int g = 100;

int&
ref_to_g (void)
{
    return g;
}

int main(void)
{
    int &ref = ref_to_g();
    ref = 200;
    //ref_to_g() = 200;
    return g;
}