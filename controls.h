class Controls {
    private:
        
    public:
        bool forward=false;
        bool left=false;
        bool right=false;
        bool reverse=false;

        Controls();
        ~Controls();
        void Update(){
            if(IsKeyDown(KEY_A)){
                left = true;
            } else {
                left = false;
            }
            if(IsKeyDown(KEY_D)){
                right = true;
            } else {
                right = false;
            }

            if (IsKeyDown(KEY_W)){
                forward = true;
            } else {
                forward = false;
            }

            if(IsKeyDown(KEY_S)){
                reverse = true;
            } else {
                reverse = false;
            }
        }
};

Controls::Controls() {
}

Controls::~Controls() {
    std::cout<<"Called Controls destructor\n";
}