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
            if(IsKeyDown(KEY_LEFT)){
                left = true;
            } else {
                left = false;
            }
            if(IsKeyDown(KEY_RIGHT)){
                right = true;
            } else {
                right = false;
            }

            if (IsKeyDown(KEY_UP)){
                forward = true;
            } else {
                forward = false;
            }

            if(IsKeyDown(KEY_DOWN)){
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