//
// Created by DEEP on 2024/8/6.
//


class Android_Input : public Input{
public:
    void registerInputCallBack(InputCallBack* callback);
private:
    InputCallBack* m_callback;
};