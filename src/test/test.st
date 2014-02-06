b = func() {
    x = 0;
    return func () {
        x.__str__();
        x = x + 1;
    };
};
 a = b();
 a();
 a();
 a();
