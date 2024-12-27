#include <vector>

using namespace std;

struct Foo
{
    // a lot of member vars - potentially expensive
    Foo() = default;
    Foo(int i, bool b, float f) : m_i(i), m_b(b),m_f(f)
	{
	}

    int m_i;
    bool m_b;
    float m_f;
}

int main()
{
    vector<Foo> v1;
    {
        Foo f1; 
	v1.push_back(f1); // pushes back as a copy
	v1.push_back(move(f1)); // steals f1's resources onto v1's internal elements
        v1.push_back(Foo(1, true, 2.f));  // takes the temporary object (also moves it under the hood)
	v1.emplace_back(1,true,2.f);

    }
    return 0;
}
