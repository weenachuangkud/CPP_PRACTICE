#include <iostream>
#include <memory>

int main()
{ 
  std::unique_ptr<int> uptr = std::make_unique<int>(10);
  std::unique_ptr<int> uptr2 = std::move(uptr);

  std::cout << *uptr2 << std::endl;  // prints 10

  return 0;
}
