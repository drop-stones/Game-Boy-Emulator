
struct Vec {
    int x;
    int y;
};

struct Vec vec1 {1, 2};

int&
ref_to_x (void)
{
    return vec1.x;
}

int main(void)
{
    int &ref = ref_to_x();
    ref = 200;
    //ref_to_g() = 200;
    return vec1.x;
}