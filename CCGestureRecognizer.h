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

#ifndef CCGestureRecognizer_h
#define CCGestureRecognizer_h

#include "cocos2d.h"



class CCGestureRecognizer : public cocos2d::Layer
{
public:
    static double timersubCocos2d(struct timeval *start, struct timeval *end)
    {
        if (! start || ! end)
        {
            return 0;
        }
        return ((end->tv_sec*1000.0+end->tv_usec/1000.0) - (start->tv_sec*1000.0+start->tv_usec/1000.0));
    }
public:
    CCGestureRecognizer();
    ~CCGestureRecognizer();
    void setTarget(cocos2d::Ref * tar, cocos2d::SEL_CallFuncO sel);
    
    virtual void onEnter() override;
    //setParent is called after the layer is added as a child
    virtual void setParent(cocos2d::Node*p);
protected:
    cocos2d::Rect frame;
    bool isRecognizing;
    
    void gestureRecognized(cocos2d::Ref * gesture);
    void stopTouchesPropagation(cocos2d::Set * pTouches, cocos2d::Event * pEvent);
    
    //utility methods
    bool isPositionBetweenBounds(cocos2d::Point pos);
    float distanceBetweenPoints(cocos2d::Point p1, cocos2d::Point p2);
    cocos2d::Set * createSetWithTouch(cocos2d::Touch * pTouch);
    
    virtual void registerWithTouchDispatcherForThis(void);
    
    //mandatory methods for subclasses
    virtual bool touchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent)=0;
    virtual void touchMoved(cocos2d::Touch * pTouch, cocos2d::Event * pEvent)=0;
    virtual void touchEnded(cocos2d::Touch * pTouch, cocos2d::Event * pEvent)=0;
    
    //if gesture is correctly recognized, cancel touch over other views (default: false)
    //NOTE: subclasses must check the value and implement it correctly
    CC_SYNTHESIZE(bool, cancelsTouchesInView, CancelsTouchesInView);
private:
    cocos2d::SEL_CallFuncO selector;
    cocos2d::Ref * target;
//    cocos2d::TouchDispatcher * dispatcher;
    cocos2d::EventDispatcher * dispatcher;
};

#endif
