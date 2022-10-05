Vector2 lerp(Vector2 A, Vector2 B, double t){
    Vector2 ret;
    ret.x = A.x + (B.x-A.x)*t;
    ret.y = A.y + (B.y-A.y)*t;

    return ret;
}

float lerp(float A, float B, float t){
    float ret;
    ret = A + (B-A)*t;

    return ret;
}
