SDL = import("libstSDL.so");
sur = SDL.Surface("1.png");
Test = state (SDL.Base) {
    onLeftClick = func (self, x, y) {
        //TODO
        "LeftClick";
        x.__str__();
        y.__str__();
        sur = SDL.Surface("1.bmp");
        SDL.ReDraw();
    };
    onRightClick = func (self, x, y) {
        //TODO
        "RightClick";
        x.__str__();
        y.__str__();
    };
    onKeyDown = func (self, key) {
        //TODO
        "KeyDown";
    };
    onKeyUp = func (self, key) {
        //TODO
        "KeyUp";
    };
    onRedraw = func (self, drawer) {
        //TODO
        drawer.Draw(sur);
    };
    onQuit = func (self) {
        return true;
    };
};

x = Test();

SDL.Run(x);
