#include "../source/std_lib_facilities.h"

struct A
{
	virtual void pvf() = 0;
};

struct B1 : A
{
	virtual void vf() { cout << "B1::vf()" << endl; }
	void f() { cout << "B1::f()" << endl; }
	void pvf() { cout << "B1::pvf()" << endl; }
};

struct D1 : B1
{
	void vf() override { cout << "D1::vf()" << endl; }
	void f() { cout << "D1::f()" << endl; }
};

struct D2 : D1
{
	void pvf() override { cout << "D2::pvf()" << endl; }
};

struct B2
{
	virtual void pvf() = 0;
};

struct D21 : B2
{
	void pvf() override { cout << "D21 string by pvf(): " << str << endl; };
private:
	string str = "D21 string";
};

struct D22 : D21
{
	void pvf() override { cout << "D22 int by pvf(): " << nb << endl; };
private:
	int nb = 22;
};

void f(B2& bbb) { bbb.pvf(); }

int main()
try {
	B1 b;
	b.vf();
	b.f();
	cout << endl;
	D1 d;
	d.vf();
	d.f();
	
	cout << endl;
	
	B1& refD = d;
	refD.vf();
	refD.f();
	
	cout << endl;
	
	D2 dd;
	dd.vf();
	dd.f();
	dd.pvf();

	cout << endl;
	D21 dd21;
	D22 dd22;
	f(dd21);
	f(dd22);

	return 0;
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}
