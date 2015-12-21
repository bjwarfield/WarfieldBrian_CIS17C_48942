#include "playerentity.h"
#include <QDebug>
#include <QGraphicsEffect>
#include <QLabel>
#include "shotentity.h"
#include "timer.h"


PlayerEntity::PlayerEntity(GameWidget *game, int x, int y):
    Entity(x,y,":/resources/sprites/player/player1sprite.png"), game(game),
    left(false),    right(false), up(false), down(false), trigger(false),
    polarize(false), moveSpeed(300),DIAGONAL(static_cast<float>(qSin(45))),
    lastShot(0), shotInterval(0.1), energy(0)
{
    polarity = WHITE;
    type = PLAYER;

    //split sprite frames into vector object
    int tileSize = 40;
    int cols = sprite->getWidth()/40;
    int rows = sprite->getHeight()/40;
    //pseudo multidimential container
    frames.resize(cols * rows);

    //copy each frame
    for(int col = 0; col < cols; col ++){
        for(int row = 0; row < rows; row++){
            frames.data()[col + (row * cols)] = s_ptr ( new Sprite(
                        sprite->getRef(),sprite->getImage().copy(
                            tileSize*col, tileSize*row, tileSize, tileSize)));
        }
    }
    currentFrame = 5;
    sprite = frames.at(currentFrame);
}

void PlayerEntity::move(double delta){

    //bound check, stop moving when reaching edge of screen
    if ((dx < 0) && (x+(delta * dx)<=sprite->getWidth()/2)){
        dx=0;
        x=sprite->getWidth()/2;
    }
    if((dx > 0) && (x+(delta * dx) >  game->width()-sprite->getWidth()/2)){
        dx = 0;
        x = game->width()-sprite->getWidth()/2;
    }
    if ((dy < 0) && (y+(delta * dy)<=sprite->getHeight()/2)){
        dy=0;
        y=sprite->getWidth()/2;
    }
    if((dy > 0) && (y +(delta * dy) >  game->height()-sprite->getHeight()/2)){
        dy = 0;
        y = game->height()-sprite->getHeight()/2;
    }

    //move
    x += (delta * dx) ;
    y += (delta * dy) ;
    //set hitbox
    hitBox.setRect(getX()-sprite->getWidth()/2,getY()- sprite->getHeight()/2,
                   sprite->getWidth(),sprite->getHeight());
}

void PlayerEntity::doLogic(){
    dx=0;
    dy=0;

    //assign movement based on keypresses
    if ((left) && (!right)) {//left
        if ((up) && (!down)) {//upLeft
            //factor for diagonnal movement speed
            setVerticalMovement(DIAGONAL * -moveSpeed);
            setHorizontalMovement(DIAGONAL * -moveSpeed);
        } else if ((down) && (!up)) {//downLeft
            setVerticalMovement(DIAGONAL * moveSpeed);
            setHorizontalMovement(DIAGONAL * -moveSpeed);
        } else {
            setHorizontalMovement(-moveSpeed);//left only
        }
    } else if ((right) && (!left)) {//right
        if ((up) && (!down)) {//up
            setVerticalMovement(DIAGONAL * -moveSpeed);
            setHorizontalMovement(DIAGONAL * moveSpeed);
        } else if ((down) && (!up)) {//down
            setVerticalMovement(DIAGONAL * moveSpeed);
            setHorizontalMovement(DIAGONAL * moveSpeed);

        } else {
            setHorizontalMovement(moveSpeed);//right only
        }
    } else if ((up) && (!down) && (!right) && (!left)) {//up
        setVerticalMovement(-moveSpeed);
    } else if ((down) && (!up) && (!right) && (!left)) {//down
        setVerticalMovement(moveSpeed);
    }

    //shot it shoot button pressed
    if(trigger){
        shoot();
    }
    //swap polarity if polariza button pressed
    if(polarize){
        polarSwap();
    }

    //ship tilt/polarity animations
    if(Timer::getTime() - lastFrameChange > 0.018){
        if(dx < 0){
            if( currentFrame > 0 +(polarity*11) ){
                currentFrame--;
                lastFrameChange = Timer::getTime();
            }
        }else if(dx == 0){
            if(currentFrame > 5+(polarity*11)){
                currentFrame--;
                lastFrameChange = Timer::getTime();
            }else if(currentFrame < 5+(polarity*11)){
                currentFrame++;
                lastFrameChange = Timer::getTime();
            }
        }else if(dx > 0){
            if(currentFrame < 10 + (polarity*11)){
                currentFrame++;
                lastFrameChange = Timer::getTime();
            }
        }
        //bind index withing range range
        currentFrame = (currentFrame + 22)%22;
        sprite = frames.at(currentFrame);
    }
}

void PlayerEntity::shoot(){
    //skip if interval has yet to pass
    if(Timer::getTime()-lastShot < shotInterval){
        return;
    }
    //capture time
    lastShot = Timer::getTime();

    e_ptr lShot(new ShotEntity(game, getX()-8, getY()-6, polarity));
    e_ptr rShot(new ShotEntity(game, getX()+8, getY()-6, polarity));
    //create new shotEntities and add them to game Qlist<e_ptr>
    game->getEntities().push_front(lShot);
    game->getEntities().push_front(rShot);

}

void PlayerEntity::polarSwap()
{
    //inverse polarity
    polarity = polarity == WHITE ? BLACK : WHITE;
    polarize = false;//unset button til next keypress

    //tilted animation fix
    if(polarity == BLACK && currentFrame == 0){
        currentFrame--;
    }else if(polarity == WHITE && currentFrame == 21){
        currentFrame ++;
    }
    currentFrame = (currentFrame + 22)%22;
//    qDebug() << "Swap";
}

void PlayerEntity::draw(QPainter *painter)
{

    QRadialGradient whiteAura(x,y, 40, x, y);
    whiteAura.setColorAt(0, QColor(0,255,255,0));
    whiteAura.setColorAt(0.5, QColor(0,255,255,0));
    whiteAura.setColorAt(0.73, QColor(0,255,255,50));
    whiteAura.setColorAt(0.75, QColor(255,255,255,80));
    whiteAura.setColorAt(0.77, QColor(0,255,255,25));
    whiteAura.setColorAt(1, QColor(0,255,255,0));

    QRadialGradient blackAura(x,y, 40, x, y);
    blackAura.setColorAt(0, QColor(255,0,0,0));
    blackAura.setColorAt(0.5, QColor(255,0,0,0));
    blackAura.setColorAt(0.73, QColor(255,0,0,50));
    blackAura.setColorAt(0.75, QColor(255,175,0,80));
    blackAura.setColorAt(0.77, QColor(255,0,0,25));
    blackAura.setColorAt(1, QColor(255,0,0,0));

    painter->setBrush(QBrush(polarity == WHITE ? whiteAura: blackAura));
    painter->setPen(Qt::transparent);
    painter->drawEllipse(QPoint(x,y),40,40);

    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect;
    int xOffset = (20.0f/(game->width()/2.0f)*x - 20);
    int yOffset = (20.0f/(game->height()/2.0f)*y - 20);

    shadow->setBlurRadius(8);
    shadow->setOffset(xOffset, yOffset);
    shadow->setColor(QColor(0,0,0,115));
    sprite->drawWithEffect(painter, getX()-20, getY()-20, shadow,20);

    //draw hitBox (debug)
    painter->setPen(polarity == WHITE ? Qt::blue : Qt::red);
    painter->drawRect(hitBox);


}

void PlayerEntity::collidedWith(e_ptr other){
    if(other->getType() == ENEMYSHOT){
        if(polarity == other->getPolarity()){
            energy = energy < 80 ? energy + 1: 80;
        }
    }

}
void PlayerEntity::setLeft(bool left)
{
    this->left = left;
}
void PlayerEntity::setRight(bool right)
{
    this->right = right;
}
void PlayerEntity::setUp(bool up)
{
    this->up = up;
}
void PlayerEntity::setDown(bool down)
{
    this->down = down;
}
void PlayerEntity::setTrigger(bool trigger)
{
    this->trigger = trigger;
}
void PlayerEntity::setPolarize(bool polarize)
{
    this->polarize = polarize;
}

PlayerEntity::~PlayerEntity()
{

}
int PlayerEntity::getEnergy() const
{
    return energy;
}







