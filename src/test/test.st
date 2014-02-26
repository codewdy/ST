a = state {};
b = state (a) {};
object.__str__();
a.__state__.__str__();
a.__str__();
b.__state__.__str__();
