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

#ifndef CCLongPressGestureRecognizer_h
#define CCLongPressGestureRecognizer_h

#include "CCGestureRecognizer.h"

#define kLongPressMinDuration 0.5

//this class is used for storing information about the long press gesture
class CCLongPress : public cocos2d::Ref
{
public:
    bool init() {return true;}
    CREATE_FUNC(CCLongPress);
    cocos2d::Point location;
};

class CCLongPressGestureRecognizer : public CCGestureRecognizer
{
public:
    bool init();
    ~CCLongPressGestureRecognizer();
    CREATE_FUNC(CCLongPressGestureRecognizer);
    void timerDidEnd(float dt);
    
    virtual bool touchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
    virtual void touchMoved(cocos2d::Touch * pTouch, cocos2d::Event * pEvent){};
    virtual void touchEnded(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
protected:
    CC_SYNTHESIZE(float, minimumPressDuration, MinimumPressDuration);
private:
    cocos2d::Point currLocation;
    cocos2d::Touch * currTouch;
    cocos2d::Event * currEvent;
    
    void stopGestureRecognition();
};

#endif
