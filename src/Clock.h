
class Clock
{
    public:
        int Currentfps = 0;
        Clock(){}
        void LimitFps(int fps);
    private:
        int lastFrameTicks = 0;
};

static Clock clock;