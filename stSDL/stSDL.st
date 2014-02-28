SDL = import("libstSDL.so");
SDL.Run;
Test = state (SDL.Base) {
    onLeftClick = func (self, x, y) {
        //TODO
        "LeftClick";
        x.__str__();
        y.__str__();
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
    };
    onQuit = func (self) {
        return true;
    };
};

x = Test();

SDL.Run(x);
