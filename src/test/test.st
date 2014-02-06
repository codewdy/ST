X = state {
    x = 0;
    setX = func(self, xxy) {
        self.x = xxy;
        xxy = 12;
    };
    setY = setX;
    print = func(self) {
        self.x.__str__();
    };
};

xx = X();
xx.print();
xx.setY(10);
xx.print();
