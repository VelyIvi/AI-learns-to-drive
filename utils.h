Vector2 lerp(Vector2 A, Vector2 B, double t){
    //read about operator overloads, and maybe implement it
    Vector2 ret;
    ret.x = A.x + (B.x-A.x)*t;
    ret.y = A.y + (B.y-A.y)*t;

    return ret;
}

double lerp(double A, double B, double t){
    double ret;
    ret = A + (B-A)*t;

    return ret;
}