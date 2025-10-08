#include <iostream>
#include "../NumberLib/Number.h"
#include "../VectorLib/Vector.h"

int main() {
    std::cout << "1. Basic operations with numbers" << '\n' << '\n';
    Number num1(11.3);
    Number num2(-16.9);
    Number num3(0.5);
    Number num4 = num3;

    std::cout << num1 << " + " << num2 << " = " << num1 + num2 << '\n';
    std::cout << num1 << " - " << num2 << " = " << num1 - num2 << '\n';
    std::cout << num1 << " * " << num2 << " = " << num1 * num2 << '\n';
    std::cout << num1 << " / " << num2 << " = " << num1 / num2 << '\n';

    std::cout << '\n' << "2. Advanced Number operators" << '\n' << '\n';

    num1 += num2;
    std::cout << "num1 += num2 => num1 = " << num1 << '\n';

    num3 -= num4;
    std::cout << "num3 -= num4 => num3 = " << num3 << '\n';

    std::cout << std::boolalpha;
    std::cout << num4 << " == " << num1 << " " << (num4 == num1) << '\n';
    std::cout << num4 << " != " << num1 << " " << (num4 != num1) << '\n';
    std::cout << num4 << " >= " << num1 << " " << (num4 >= num1) << '\n';
    std::cout << num4 << " <= " << num1 << " " << (num4 <= num1) << '\n';

    std::cout << '\n' << "3. Constants" << '\n' << '\n';

    std::cout << "ZERO = " << Number::ZERO << '\n';
    std::cout << "ONE = " << Number::ONE << '\n';

    std::cout << '\n' << "4. Method for creating a number with a given value" << '\n' << '\n';

    double value;
    std::cout << "Input the value : ";
    std::cin >> value;

    Number seeking = createNumber(value);
    std::cout << "The created number has the value of " << seeking;

    std::cout << '\n' << "5. Basic operations with vectors" << '\n' << '\n';

    Vector vec1(0.5, 0.7);
    Vector vec2(1.2, -0.3);
    Vector vec3(-0.8, 1.1);
    Vector vec4 = vec1;

    std::cout << "vec1 = " << vec1 << '\n';
    std::cout << "vec2 = " << vec2 << '\n';
    std::cout << "vec3 = " << vec3 << '\n';
    std::cout << "vec4 = " << vec4 << '\n';

    std::cout << vec1 << " + " << vec2 << " = " << vec1 + vec2 << '\n';
    std::cout << vec1 << " - " << vec2 << " = " << vec1 - vec2 << '\n';
    std::cout << vec1 << " * " << num3 << " = " << vec1 * num3 << '\n';
    std::cout << vec1 << " / " << num1 << " = " << vec1 / num1 << '\n';
    std::cout << "-" << vec1 << " = " << -vec1 << '\n';

    std::cout << '\n' << "6. Vector comparison" << '\n' << '\n';

    std::cout << vec1 << " == " << vec4 << " " << (vec1 == vec4) << '\n';
    std::cout << vec1 << " == " << vec2 << " " << (vec1 == vec2) << '\n';
    std::cout << vec1 << " != " << vec2 << " " << (vec1 != vec2) << '\n';

    std::cout << '\n' << "7. Vector methods" << '\n' << '\n';

    std::cout << "Polar radius of " << vec1 << " = " << vec1.getPolarRadius() << '\n';
    std::cout << "Polar angle of " << vec1 << " = " << vec1.getPolarAngle() << '\n';
    std::cout << "X coordinate of " << vec1 << " = " << vec1.getX() << '\n';
    std::cout << "Y coordinate of " << vec1 << " = " << vec1.getY() << '\n';

    std::cout << '\n' << "8. Vector constants" << '\n' << '\n';

    std::cout << "ZERO_ZERO = " << Vector::ZERO_ZERO << '\n';
    std::cout << "ONE_ONE = " << Vector::ONE_ONE << '\n';


    return 0;
}
