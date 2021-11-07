# Exercise

Implement the following functions:

```cpp
class Book
{
    friend std::istream &operator>>(std::istream &, Book &);
    friend std::ostream &operator<<(std::ostream &, const Book &);

public:
    Book() = default;
    Book(std::string name_, std::string author_, std::uint32_t pubyear_);
    ~Book() noexcept = default;

    bool operator==(const Book &other) const;
    bool operator!=(const Book &other) const;

private:
    std::string name;
    std::string author;
    std::uint32_t pubyear;
};

std::istream &operator>>(std::istream &, Book &);
std::ostream &operator<<(std::ostream &, const Book &);
```

## Main Function

```cpp
int main()
{
    Book b1("Harry Potter - Stein der Weisen", "J. K. Rowling", 1997);
    Book b2("Harry Potter - Die Kammer des Schreckens", "J. K. Rowling", 1998);

    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;

    std::cout << std::boolalpha;
    std::cout << (b1 == b2) << std::endl;
    std::cout << (b1 == b1) << std::endl;

    return 0;
}
```
