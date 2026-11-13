#include <cstdio>

struct Engine
{
  char maker[16];
  int year;
  double speed;
};

struct Car
{
  int num;
  double gas;
  Engine engine;
};

void engine_echo(Engine engine)
{
  printf("エンジンのメーカー: %s\n", engine.maker);
  printf("エンジンの製造年:   %d 年\n", engine.year);
  printf("エンジンの最高速度: %.2f km/h\n", engine.speed);
}
void car_echo(Car car)
{
  printf("車のナンバー:       %d\n", car.num);
  printf("車のガソリン量:     %.2f L\n", car.gas);
  engine_echo(car.engine);
  printf("------------------------------\n");
}
int main()
{
  Engine engine[4] = {
      {"Yamaha", 2015, 160},
      {"Honda", 2018, 150},
      {"SUzuki", 2020, 150},
      {"Kawasaki", 2022, 200}};

  Car cars[4] = {
      {2525, 25.5, engine[0]},
      {8888, 15.0, engine[1]},
      {3296, 10.0, engine[2]},
      {1111, 30.0, engine[3]}};

  for (int i = 0; i < 4; i++)
  {
    car_echo(cars[i]);
  }

  return 0;
}