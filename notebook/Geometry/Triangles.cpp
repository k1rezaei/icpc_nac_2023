pt bary(pt A, pt B, pt C, ld a, ld b, ld c) {
    return (A*a + B*b + C*c) / (a + b + c);
}
pt centroid(pt A, pt B, pt C) {
    // geometric center of mass
    return bary(A, B, C, 1, 1, 1);
}
pt circumcenter(pt A, pt B, pt C) {
    // intersection of perpendicular bisectors
    double a = norm(B - C), b = norm(C - A), c = norm(A - B);
    return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
}

pt incenter(pt A, pt B, pt C) {
    // intersection of internal angle bisectors
    return bary(A, B, C, abs(B-C), abs(A-C), abs(A-B));
}

pt orthocenter(pt A, pt B, pt C) {
    // intersection of altitudes
    double a = norm(B - C), b = norm(C - A), c = norm(A - B);
    return bary(A, B, C, (a+b-c)*(c+a-b), (b+c-a)*(a+b-c), (c+a-b)*(b+c-a));
}

pt excenter(pt A, pt B, pt C) {
    // intersection of two external angle bisectors
    double a = abs(B - C), b = abs(A - C), c = abs(A - B);
    return bary(A, B, C, -a, b, c);

    //// NOTE: there are three excenters
    // return bary(A, B, C, a, -b, c);
    // return bary(A, B, C, a, b, -c);
}
