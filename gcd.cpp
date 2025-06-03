int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);  // Recursive call
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a; //iteration
}