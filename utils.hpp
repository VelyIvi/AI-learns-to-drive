float get_random(float start, float end){
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(start, end); // rage 0 - 1
    return dis(e);
}


Vector2 lerp(Vector2 A, Vector2 B, double t){
    Vector2 ret;
    ret.x = A.x + (B.x-A.x)*t;
    ret.y = A.y + (B.y-A.y)*t;

    return ret;
}

float lerp(float A, float B, float t){ //https://stackoverflow.com/questions/4353525/floating-point-linear-interpolation
    float ret;
    ret = A + (B-A)*t;

    return ret;
}

//class Intersect {
//    public:
//        Intersect(bool h, float l, Vector2 p): hit(h), length(l), hitPoint(p){}
//        Intersect();
//        bool hit;
//        float length;
//        Vector2 hitPoint;
//};

//Intersect getIntersection(Vector2 line1_1, Vector2 line1_2, Vector2 line2_1, Vector2 line2_2){
//    const float x1 = line1_1.x;
//    const float y1 = line1_1.y;
//    const float x2 = line1_2.x;
//    const float y2 = line1_2.y;
//
//    const float x3 = line2_1.x;
//    const float y3 = line2_1.y;
//    const float x4 = line2_2.x;
//    const float y4 = line2_2.y;
//
//    const float den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
//    if (den == 0){
//        return {false, 0, {x2, y2}};
//    }
//
//    const float t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/den;
//    const float u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/den;
//
//    if (t>0 && t<1 && u>0 && u<1){ //to have unlimited length remove t<1 //for some reason I have to remove t<1 instead if u<1 have no idea why won't fix
//        Vector2 retX = {(x3+u*(x4-x3)), (y3+u*(y4-y3))};
//        float length = sqrt(pow(retX.x-x1, 2) + pow(retX.y-y1, 2));
//        return {true, length, retX};
//    } else {
//        return {false, 0, {x2, y2}};
//    }
//}

Vector4 getIntersection(Vector2 line1_1, Vector2 line1_2, Vector2 line2_1, Vector2 line2_2, float maxLength){
    const float x1 = line1_1.x;
    const float y1 = line1_1.y;
    const float x2 = line1_2.x;
    const float y2 = line1_2.y;

    const float x3 = line2_1.x;
    const float y3 = line2_1.y;
    const float x4 = line2_2.x;
    const float y4 = line2_2.y;

    const float den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    if (den == 0){
        return {x2, y2, maxLength, 0};
    }

    const float t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/den;
    const float u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/den;

    if (t>0 && t<1 && u>0 && u<1){ //to have unlimited length remove t<1 //for some reason I have to remove t<1 instead if u<1 have no idea why won't fix
        Vector2 retX = {(x3+u*(x4-x3)), (y3+u*(y4-y3))};
        float length = sqrt(pow(retX.x-x1, 2) + pow(retX.y-y1, 2));
        return {retX.x, retX.y, length, 1};
    } else {
        return {x2, y2, maxLength, 0};
    }
}