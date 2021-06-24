#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"

class CCollisionManager final :
    public CManagerClassBase<CCollisionManager>
{
private :
    list<class CCollisionComponent*> CreatedCollisions;
    list<class CCollisionComponent*> UsedCollisions;
    list<class CCollisionComponent*> DestroyedCollisions;


private : 
    bool DoCollisionTestCircleToCircle(
        class CCollisionComponent* circle1, class CCollisionComponent* circle2);

    bool DoCollisionTestRectToRect(
        class CCollisionComponent* rect1, class CCollisionComponent* rect2);

    bool DoCollisionTestRectToCircle(class CCollisionComponent* rect, class CCollisionComponent* circle);

public :
    void DoCollisionTest();

    void RegisterCollision(class CCollisionComponent* collision);
    void UnRegisterCollision(class CCollisionComponent* collision);

};

