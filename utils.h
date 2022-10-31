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

Vector2 getIntersection(Vector2 point1_1, Vector2 point1_2, Vector2 point2_1, Vector2 point2_2){
    const float x1 = point1_1.x;
    const float y1 = point1_1.y;
    const float x2 = point1_2.x;
    const float y2 = point1_2.y;

    const float x3 = point2_1.x;
    const float y3 = point2_1.y;
    const float x4 = point2_2.x;
    const float y4 = point2_2.y;

    

    const float den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    if (den == 0){
        return {0, 0};
    }

    const float t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/den;
    const float u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/den;
    std::cout<<"t: "<<t<<"   u: "<<u<<"\n";

    if (t>0 && t<1 && u>0){ //to have unlimited length remove u<1
        Vector2 retX = {(x1+t*(x2-x1)), (y1+t*(y2-y1))};
        return retX;
    } else {
        return {0, 0};
    }
}