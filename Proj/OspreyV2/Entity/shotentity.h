#ifndef SHOTENTITY_H
#define SHOTENTITY_H

#include "Main/gamewidget.h"
#include "Entity/entity.h"
#include <Vector>


class ShotEntity: public Entity
{
protected:
   int shotSpeed;
   bool hit;
   int dmg;
   Vector<s_ptr> fragFrames;
   int currentFrag;

public:
   ShotEntity(GameState *game, int x, int y, polarType polarity);
   void draw(QPainter *painter) Q_DECL_OVERRIDE;
   void move(double delta) Q_DECL_OVERRIDE;
   void move(double delta, float xShift) Q_DECL_OVERRIDE;
   void move(double delta, float xShift, float yShift) Q_DECL_OVERRIDE;

   // Entity interface
   void doLogic(double delta) Q_DECL_OVERRIDE;
   void collidedWith(const e_ptr &other) Q_DECL_OVERRIDE;

   ~ShotEntity();
   bool getHit() const ;
   int getDmg() const;
};

#endif // SHOTENTITY_H
