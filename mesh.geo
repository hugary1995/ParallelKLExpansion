a = 1;
b = 2;
e = 0.5;

Point(1) = {0, 0, 0, e};
Point(2) = {a, 0, 0, e};
Point(3) = {a, b, 0, e};
Point(4) = {0, b, 0, e};

Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};

Line Loop(1) = {1,2,3,4};
Plane Surface(1) = {1};

Physical Surface("all") = {1};
Physical Line("top") = {3};
Physical Line("bottom") = {1};
Physical Line("left") = {4};
Physical Line("right") = {2};
