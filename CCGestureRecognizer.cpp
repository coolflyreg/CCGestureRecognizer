/****************************************************************************
Copyright (c) 2013 Artavazd Barseghyan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCGestureRecognizer.h"

USING_NS_CC;

CCGestureRecognizer::CCGestureRecognizer()
{
    isRecognizing = false;
    
//    setTouchEnabled(true);
    setCancelsTouchesInView(false);
}

CCGestureRecognizer::~CCGestureRecognizer()
{
    dispatcher->removeEventListenersForTarget(this);
//    dispatcher->removeDelegate(this);
}

void CCGestureRecognizer::onEnter()
{
    Layer::onEnter();
    dispatcher = this->getEventDispatcher();//Director::getInstance()->getEventDispatcher();
    this->registerWithTouchDispatcherForThis();
}

void CCGestureRecognizer::setTarget(Ref * tar, SEL_CallFuncO sel)
{
    target = tar;
    selector = sel;
}

float CCGestureRecognizer::distanceBetweenPoints(Point p1, Point p2)
{
    float deltaX = p2.x-p1.x;
    float deltaY = p2.y-p1.y;
    return fabs(sqrtf(deltaX*deltaX+deltaY*deltaY));
}

void CCGestureRecognizer::stopTouchesPropagation(Set * pTouches, Event * pEvent)
{
    //hack! cancel touch so it won't propagate
//    dispatcher->touchesCancelled(pTouches, pEvent);
    dispatcher->dispatchEvent(pEvent);//
}

void CCGestureRecognizer::setParent(Node*p)
{
    Layer::setParent(p);
    
    if (p!=NULL) {
        Size size = p->getContentSize();
        setContentSize(size);
        setPosition(p->getPosition());
        frame = p->getBoundingBox();
        frame.origin = p->convertToWorldSpace(frame.origin);
    }
}

Set * CCGestureRecognizer::createSetWithTouch(Touch * pTouch)
{
    Set * set = new Set();
    set->addObject(pTouch);
    return set;
}

void CCGestureRecognizer::registerWithTouchDispatcherForThis()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = CC_CALLBACK_2(CCGestureRecognizer::touchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CCGestureRecognizer::touchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CCGestureRecognizer::touchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//    dispatcher->addEventListenerWithSceneGraphPriority(cocos2d::EventListener *listener, this);
//    dispatcher->addTargetedDelegate(this, -256, false);
}

bool CCGestureRecognizer::isPositionBetweenBounds(Point pos)
{
    frame = getBoundingBox();
    frame.origin = convertToWorldSpace(frame.origin);
    return frame.containsPoint(pos);
}

void CCGestureRecognizer::gestureRecognized(cocos2d::Ref * gesture)
{
    if (target && selector) (target->*selector)(gesture); //call selector
}
