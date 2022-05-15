class Particle {
public:
    Particle(double pos[3], double dir[3], int spd, double ang[3],
             int size, double rgb[3], int material, int age, int shape);
    double pos[3]{};
    double dir[3]{};
    int spd;
    double ang[3]{};
    int size;
    double rgb[3]{};
    int material;
    int age;
    int shape;
    //bool delectFlag;
    void move();
    void move_with_fract(double fraction);
    void apply_grav(float grav);
    bool check_delet();
};

