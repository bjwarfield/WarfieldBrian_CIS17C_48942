#include <QtCore>
#include "GameState/menustate.h"
#include "Main/gamewidget.h"

MenuState::MenuState(GameStateManager *gsm):
    GameState(gsm), logo(":/title/osprey-logo.png"),
    grayFont(":/tilesets/AgencyGray34.png", ":/tilesets/Agency34.dat" ),
    redFont(":/tilesets/AgencyRed34.png", ":/tilesets/Agency34.dat" )
{


    currentChoice = 0;

    option.resize(4);
    option[0] = "Start";
    option[1] = "User Control Panel";
    option[2] = "Level Editor";
    option[3] = "Quit";

    bg = QSharedPointer<Background>(new Background(":/backgrounds/clouds_01.png", 1.2));
    bg->setMovement(-120,50);

    le = NULL;
    ucp = NULL;
    init();

}



void MenuState::init()
{

}

void MenuState::gameUpdate(double delta)
{
    bg->gameUpdate(delta);

}

void MenuState::gameDraw(QPainter *painter)
{
    bg->gameRender(painter);
    logo.draw(painter, gsm->getWidget()->width()/2, 200);



    for(int i = 0; i < option.size(); i++){
        QString s = option.at(i);


        if(i == currentChoice){
            selectedFont = &redFont;
//            painter->setPen(Qt::red);
//            painter->setBrush(QBrush(Qt::white));
            QPainterPath path;
            path.addRoundedRect(
                        QRectF((gsm->getWidget()->width()-255) / 2, 340 + i * 45,
                               260, 39),8,8);
            painter->fillPath(path, QBrush(QColor(255,255,255,100)));
//            painter->fillRect((gsm->getWidget()->width()-255)/2, 340 + i*45,255,39,QBrush(Qt::white));
        }else{
            selectedFont = &grayFont;
//            painter->setPen(Qt::gray);
        }

        selectedFont->draw(painter,s, (gsm->getWidget()->width()
                           - selectedFont->getStringWidth(s))/2,340+i*45);
//        QFont f = painter->font();
//        f.setPointSize(34);
//        painter->setFont(f);
//        painter->drawText((GameWidget::WIDTH - painter->fontMetrics().width(s))/2,340 + i * 45, s);

    }


}

void MenuState::keyPressed(int k)
{
    switch(k){
    case Qt::Key_Return:
        select();
        break;
    case Qt::Key_Up:
        currentChoice--;
        if(currentChoice < 0) currentChoice = option.size() - 1;
        break;
    case Qt::Key_Down:
        currentChoice++;
        if(currentChoice > option.size() - 1) currentChoice = 0;
        break;
    }

}

void MenuState::keyReleased(int k)
{
    Q_UNUSED(k);
}


void MenuState::select()
{
    switch(currentChoice){
    case 0:
        //start game
        gsm->setState(GameStateManager::LEVEL1STATE);
        break;
    case 1:
        //User Control Panel
        if(!ucp){
            ucp = new UserControlPanel(gsm->getWidget());
        }
        ucp->show();
        break;
    case 2:
        //level editor
        if(!le){
            le = new levelEditor(gsm->getWidget());
        }
        le->show();
        break;
    case 3:
        //close app
        gsm->getWidget()->endGame();
        QTimer::singleShot(250,qApp,SLOT(quit()));
        break;
    }
}

MenuState::~MenuState()
{

}
