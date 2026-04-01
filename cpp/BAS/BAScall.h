#pragma once
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  BAScall
//
// Author:  Eliot Muir
//
// Description:
//
// A closure takes the leading arguments at run time and captures the trailing
// arguments up front. This is the actual usage pattern:
//
// void BASrunGreeting(BAScall1<const BASstring&>* pCall){
//    pCall->run(BASstring("Greeting"));
// }
//
// void BAShello(const BASstring& Prefix, int Value);
//
// BASrunGreeting(BAScallBind1(&BAShello, 42));
//
// class BASexample {
// public:
//    void print(const BASstring& Prefix, int Value);
// };
//
// BASexample Example;
// BASrunGreeting(BAScallBind1(&Example, &BASexample::print, 99));
// WARNING - this code is generated from a Lua script.  Scroll to the end.
//-----------------------------------------------------------------------------

class BAScall0{
public:
	BAScall0(){}
	virtual ~BAScall0(){}
	virtual void run() const=0;
	void runAndDelete(){run();delete this;}
private:
	BAScall0(const BAScall0& Orig);
	BAScall0& operator=(const BAScall0& Orig);
};

template <typename A1>
class BAScall1{
public:
	BAScall1(){}
	virtual ~BAScall1(){}
	virtual void run(A1 a1) const=0;
	void runAndDelete(A1 a1){run(a1);delete this;}
private:
	BAScall1(const BAScall1& Orig);
	BAScall1& operator=(const BAScall1& Orig);
};

template <typename A1,typename A2>
class BAScall2{
public:
	BAScall2(){}
	virtual ~BAScall2(){}
	virtual void run(A1 a1,A2 a2) const=0;
	void runAndDelete(A1 a1,A2 a2){run(a1,a2);delete this;}
private:
	BAScall2(const BAScall2& Orig);
	BAScall2& operator=(const BAScall2& Orig);
};

template <typename A1,typename A2,typename A3>
class BAScall3{
public:
	BAScall3(){}
	virtual ~BAScall3(){}
	virtual void run(A1 a1,A2 a2,A3 a3) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3){run(a1,a2,a3);delete this;}
private:
	BAScall3(const BAScall3& Orig);
	BAScall3& operator=(const BAScall3& Orig);
};

template <typename A1,typename A2,typename A3,typename A4>
class BAScall4{
public:
	BAScall4(){}
	virtual ~BAScall4(){}
	virtual void run(A1 a1,A2 a2,A3 a3,A4 a4) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3,A4 a4){run(a1,a2,a3,a4);delete this;}
private:
	BAScall4(const BAScall4& Orig);
	BAScall4& operator=(const BAScall4& Orig);
};

template <typename A1,typename A2,typename A3,typename A4,typename A5>
class BAScall5{
public:
	BAScall5(){}
	virtual ~BAScall5(){}
	virtual void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){run(a1,a2,a3,a4,a5);delete this;}
private:
	BAScall5(const BAScall5& Orig);
	BAScall5& operator=(const BAScall5& Orig);
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class BAScall6{
public:
	BAScall6(){}
	virtual ~BAScall6(){}
	virtual void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){run(a1,a2,a3,a4,a5,a6);delete this;}
private:
	BAScall6(const BAScall6& Orig);
	BAScall6& operator=(const BAScall6& Orig);
};

 class BASc0f0:public BAScall0{
public:
	typedef void (*F)();
	BASc0f0():_pF(0){}
	BASc0f0(F pF):_pF(pF){}
	~BASc0f0(){}
	void run() const {(*_pF)();}
private:
	F _pF;
};


inline BASc0f0* BAScallBind0(void (*fn)()){return new BASc0f0(fn);}

template <typename C1> class BASc0f1:public BAScall0{
public:
	typedef void (*F)(C1 c1);
	BASc0f1():_pF(0){}
	BASc0f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc0f1(){}
	void run() const {(*_pF)(_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename C1>
inline BASc0f1<C1>* BAScallBind0(void (*fn)(C1),C1 c1){return new BASc0f1<C1>(fn,c1);}

template <typename C1,typename C2> class BASc0f2:public BAScall0{
public:
	typedef void (*F)(C1 c1,C2 c2);
	BASc0f2():_pF(0){}
	BASc0f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc0f2(){}
	void run() const {(*_pF)(_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename C1,typename C2>
inline BASc0f2<C1,C2>* BAScallBind0(void (*fn)(C1,C2),C1 c1,C2 c2){return new BASc0f2<C1,C2>(fn,c1,c2);}

template <typename C1,typename C2,typename C3> class BASc0f3:public BAScall0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3);
	BASc0f3():_pF(0){}
	BASc0f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc0f3(){}
	void run() const {(*_pF)(_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename C1,typename C2,typename C3>
inline BASc0f3<C1,C2,C3>* BAScallBind0(void (*fn)(C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc0f3<C1,C2,C3>(fn,c1,c2,c3);}

template <typename C1,typename C2,typename C3,typename C4> class BASc0f4:public BAScall0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3,C4 c4);
	BASc0f4():_pF(0){}
	BASc0f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc0f4(){}
	void run() const {(*_pF)(_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename C1,typename C2,typename C3,typename C4>
inline BASc0f4<C1,C2,C3,C4>* BAScallBind0(void (*fn)(C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc0f4<C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename C1,typename C2,typename C3,typename C4,typename C5> class BASc0f5:public BAScall0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc0f5():_pF(0){}
	BASc0f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc0f5(){}
	void run() const {(*_pF)(_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc0f5<C1,C2,C3,C4,C5>* BAScallBind0(void (*fn)(C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc0f5<C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc0f6:public BAScall0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc0f6():_pF(0){}
	BASc0f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc0f6(){}
	void run() const {(*_pF)(_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc0f6<C1,C2,C3,C4,C5,C6>* BAScallBind0(void (*fn)(C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc0f6<C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1> class BASc1f0:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1);
	BASc1f0():_pF(0){}
	BASc1f0(F pF):_pF(pF){}
	~BASc1f0(){}
	void run(A1 a1) const {(*_pF)(a1);}
private:
	F _pF;
};

template <typename A1>
inline BASc1f0<A1>* BAScallBind1(void (*fn)(A1)){return new BASc1f0<A1>(fn);}

template <typename A1,typename C1> class BASc1f1:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1);
	BASc1f1():_pF(0){}
	BASc1f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc1f1(){}
	void run(A1 a1) const {(*_pF)(a1,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename C1>
inline BASc1f1<A1,C1>* BAScallBind1(void (*fn)(A1,C1),C1 c1){return new BASc1f1<A1,C1>(fn,c1);}

template <typename A1,typename C1,typename C2> class BASc1f2:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2);
	BASc1f2():_pF(0){}
	BASc1f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc1f2(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename C1,typename C2>
inline BASc1f2<A1,C1,C2>* BAScallBind1(void (*fn)(A1,C1,C2),C1 c1,C2 c2){return new BASc1f2<A1,C1,C2>(fn,c1,c2);}

template <typename A1,typename C1,typename C2,typename C3> class BASc1f3:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3);
	BASc1f3():_pF(0){}
	BASc1f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc1f3(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename C1,typename C2,typename C3>
inline BASc1f3<A1,C1,C2,C3>* BAScallBind1(void (*fn)(A1,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc1f3<A1,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename C1,typename C2,typename C3,typename C4> class BASc1f4:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc1f4():_pF(0){}
	BASc1f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc1f4(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename C1,typename C2,typename C3,typename C4>
inline BASc1f4<A1,C1,C2,C3,C4>* BAScallBind1(void (*fn)(A1,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc1f4<A1,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc1f5:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc1f5():_pF(0){}
	BASc1f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc1f5(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename A1,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc1f5<A1,C1,C2,C3,C4,C5>* BAScallBind1(void (*fn)(A1,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc1f5<A1,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc1f6:public BAScall1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc1f6():_pF(0){}
	BASc1f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc1f6(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc1f6<A1,C1,C2,C3,C4,C5,C6>* BAScallBind1(void (*fn)(A1,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc1f6<A1,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2> class BASc2f0:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2);
	BASc2f0():_pF(0){}
	BASc2f0(F pF):_pF(pF){}
	~BASc2f0(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2);}
private:
	F _pF;
};

template <typename A1,typename A2>
inline BASc2f0<A1,A2>* BAScallBind2(void (*fn)(A1,A2)){return new BASc2f0<A1,A2>(fn);}

template <typename A1,typename A2,typename C1> class BASc2f1:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1);
	BASc2f1():_pF(0){}
	BASc2f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc2f1(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename C1>
inline BASc2f1<A1,A2,C1>* BAScallBind2(void (*fn)(A1,A2,C1),C1 c1){return new BASc2f1<A1,A2,C1>(fn,c1);}

template <typename A1,typename A2,typename C1,typename C2> class BASc2f2:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2);
	BASc2f2():_pF(0){}
	BASc2f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc2f2(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename C1,typename C2>
inline BASc2f2<A1,A2,C1,C2>* BAScallBind2(void (*fn)(A1,A2,C1,C2),C1 c1,C2 c2){return new BASc2f2<A1,A2,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename C1,typename C2,typename C3> class BASc2f3:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3);
	BASc2f3():_pF(0){}
	BASc2f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc2f3(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename C1,typename C2,typename C3>
inline BASc2f3<A1,A2,C1,C2,C3>* BAScallBind2(void (*fn)(A1,A2,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc2f3<A1,A2,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4> class BASc2f4:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc2f4():_pF(0){}
	BASc2f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc2f4(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4>
inline BASc2f4<A1,A2,C1,C2,C3,C4>* BAScallBind2(void (*fn)(A1,A2,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc2f4<A1,A2,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc2f5:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc2f5():_pF(0){}
	BASc2f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc2f5(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc2f5<A1,A2,C1,C2,C3,C4,C5>* BAScallBind2(void (*fn)(A1,A2,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc2f5<A1,A2,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc2f6:public BAScall2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc2f6():_pF(0){}
	BASc2f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc2f6(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc2f6<A1,A2,C1,C2,C3,C4,C5,C6>* BAScallBind2(void (*fn)(A1,A2,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc2f6<A1,A2,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3> class BASc3f0:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3);
	BASc3f0():_pF(0){}
	BASc3f0(F pF):_pF(pF){}
	~BASc3f0(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3>
inline BASc3f0<A1,A2,A3>* BAScallBind3(void (*fn)(A1,A2,A3)){return new BASc3f0<A1,A2,A3>(fn);}

template <typename A1,typename A2,typename A3,typename C1> class BASc3f1:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1);
	BASc3f1():_pF(0){}
	BASc3f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc3f1(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename C1>
inline BASc3f1<A1,A2,A3,C1>* BAScallBind3(void (*fn)(A1,A2,A3,C1),C1 c1){return new BASc3f1<A1,A2,A3,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename C1,typename C2> class BASc3f2:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2);
	BASc3f2():_pF(0){}
	BASc3f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc3f2(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2>
inline BASc3f2<A1,A2,A3,C1,C2>* BAScallBind3(void (*fn)(A1,A2,A3,C1,C2),C1 c1,C2 c2){return new BASc3f2<A1,A2,A3,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3> class BASc3f3:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3);
	BASc3f3():_pF(0){}
	BASc3f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc3f3(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3>
inline BASc3f3<A1,A2,A3,C1,C2,C3>* BAScallBind3(void (*fn)(A1,A2,A3,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc3f3<A1,A2,A3,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4> class BASc3f4:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc3f4():_pF(0){}
	BASc3f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc3f4(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4>
inline BASc3f4<A1,A2,A3,C1,C2,C3,C4>* BAScallBind3(void (*fn)(A1,A2,A3,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc3f4<A1,A2,A3,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc3f5:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc3f5():_pF(0){}
	BASc3f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc3f5(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc3f5<A1,A2,A3,C1,C2,C3,C4,C5>* BAScallBind3(void (*fn)(A1,A2,A3,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc3f5<A1,A2,A3,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc3f6:public BAScall3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc3f6():_pF(0){}
	BASc3f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc3f6(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc3f6<A1,A2,A3,C1,C2,C3,C4,C5,C6>* BAScallBind3(void (*fn)(A1,A2,A3,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc3f6<A1,A2,A3,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3,typename A4> class BASc4f0:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4);
	BASc4f0():_pF(0){}
	BASc4f0(F pF):_pF(pF){}
	~BASc4f0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3,typename A4>
inline BASc4f0<A1,A2,A3,A4>* BAScallBind4(void (*fn)(A1,A2,A3,A4)){return new BASc4f0<A1,A2,A3,A4>(fn);}

template <typename A1,typename A2,typename A3,typename A4,typename C1> class BASc4f1:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1);
	BASc4f1():_pF(0){}
	BASc4f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc4f1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1>
inline BASc4f1<A1,A2,A3,A4,C1>* BAScallBind4(void (*fn)(A1,A2,A3,A4,C1),C1 c1){return new BASc4f1<A1,A2,A3,A4,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2> class BASc4f2:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2);
	BASc4f2():_pF(0){}
	BASc4f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc4f2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2>
inline BASc4f2<A1,A2,A3,A4,C1,C2>* BAScallBind4(void (*fn)(A1,A2,A3,A4,C1,C2),C1 c1,C2 c2){return new BASc4f2<A1,A2,A3,A4,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3> class BASc4f3:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3);
	BASc4f3():_pF(0){}
	BASc4f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc4f3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3>
inline BASc4f3<A1,A2,A3,A4,C1,C2,C3>* BAScallBind4(void (*fn)(A1,A2,A3,A4,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc4f3<A1,A2,A3,A4,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4> class BASc4f4:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc4f4():_pF(0){}
	BASc4f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc4f4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4>
inline BASc4f4<A1,A2,A3,A4,C1,C2,C3,C4>* BAScallBind4(void (*fn)(A1,A2,A3,A4,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc4f4<A1,A2,A3,A4,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc4f5:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc4f5():_pF(0){}
	BASc4f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc4f5(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc4f5<A1,A2,A3,A4,C1,C2,C3,C4,C5>* BAScallBind4(void (*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc4f5<A1,A2,A3,A4,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc4f6:public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc4f6():_pF(0){}
	BASc4f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc4f6(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc4f6<A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>* BAScallBind4(void (*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc4f6<A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3,typename A4,typename A5> class BASc5f0:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5);
	BASc5f0():_pF(0){}
	BASc5f0(F pF):_pF(pF){}
	~BASc5f0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5>
inline BASc5f0<A1,A2,A3,A4,A5>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5)){return new BASc5f0<A1,A2,A3,A4,A5>(fn);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1> class BASc5f1:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1);
	BASc5f1():_pF(0){}
	BASc5f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc5f1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1>
inline BASc5f1<A1,A2,A3,A4,A5,C1>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5,C1),C1 c1){return new BASc5f1<A1,A2,A3,A4,A5,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2> class BASc5f2:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2);
	BASc5f2():_pF(0){}
	BASc5f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc5f2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2>
inline BASc5f2<A1,A2,A3,A4,A5,C1,C2>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5,C1,C2),C1 c1,C2 c2){return new BASc5f2<A1,A2,A3,A4,A5,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3> class BASc5f3:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3);
	BASc5f3():_pF(0){}
	BASc5f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc5f3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3>
inline BASc5f3<A1,A2,A3,A4,A5,C1,C2,C3>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc5f3<A1,A2,A3,A4,A5,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4> class BASc5f4:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc5f4():_pF(0){}
	BASc5f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc5f4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4>
inline BASc5f4<A1,A2,A3,A4,A5,C1,C2,C3,C4>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc5f4<A1,A2,A3,A4,A5,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc5f5:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc5f5():_pF(0){}
	BASc5f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc5f5(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc5f5<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc5f5<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc5f6:public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc5f6():_pF(0){}
	BASc5f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc5f6(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc5f6<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>* BAScallBind5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc5f6<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6> class BASc6f0:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6);
	BASc6f0():_pF(0){}
	BASc6f0(F pF):_pF(pF){}
	~BASc6f0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
inline BASc6f0<A1,A2,A3,A4,A5,A6>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6)){return new BASc6f0<A1,A2,A3,A4,A5,A6>(fn);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1> class BASc6f1:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1);
	BASc6f1():_pF(0){}
	BASc6f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~BASc6f1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1>
inline BASc6f1<A1,A2,A3,A4,A5,A6,C1>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6,C1),C1 c1){return new BASc6f1<A1,A2,A3,A4,A5,A6,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2> class BASc6f2:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2);
	BASc6f2():_pF(0){}
	BASc6f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~BASc6f2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2>
inline BASc6f2<A1,A2,A3,A4,A5,A6,C1,C2>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2),C1 c1,C2 c2){return new BASc6f2<A1,A2,A3,A4,A5,A6,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3> class BASc6f3:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3);
	BASc6f3():_pF(0){}
	BASc6f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc6f3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3>
inline BASc6f3<A1,A2,A3,A4,A5,A6,C1,C2,C3>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc6f3<A1,A2,A3,A4,A5,A6,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4> class BASc6f4:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc6f4():_pF(0){}
	BASc6f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc6f4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4>
inline BASc6f4<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc6f4<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc6f5:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc6f5():_pF(0){}
	BASc6f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc6f5(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4,_c5);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc6f5<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc6f5<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc6f6:public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc6f6():_pF(0){}
	BASc6f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc6f6(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc6f6<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>* BAScallBind6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc6f6<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <class T> class BASc0m0 : public BAScall0{
public:
	typedef void (T::*F)();
	BASc0m0():_pF(0),_pObj(0){}
	BASc0m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc0m0(){}
	void run() const {(_pObj->*_pF)();}
private:
	T* _pObj;
	F _pF;
};

template <class T>
inline BASc0m0<T>* BAScallBind0(T* pObj, void (T::*fn)()){return new BASc0m0<T>(pObj,fn);}

template <class T>
inline BASc0m0<T>* BAScallBind0(T* pObj, void (T::*fn)() const){return new BASc0m0<T>(pObj,(void (T::*)())fn);}

template <class T,typename C1> class BASc0m1 : public BAScall0{
public:
	typedef void (T::*F)(C1 c1);
	BASc0m1():_pF(0),_pObj(0){}
	BASc0m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc0m1(){}
	void run() const {(_pObj->*_pF)(_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename C1>
inline BASc0m1<T,C1>* BAScallBind0(T* pObj, void (T::*fn)(C1),C1 c1){return new BASc0m1<T,C1>(pObj,fn,c1);}

template <class T,typename C1>
inline BASc0m1<T,C1>* BAScallBind0(T* pObj, void (T::*fn)(C1) const,C1 c1){return new BASc0m1<T,C1>(pObj,(void (T::*)(C1))fn,c1);}

template <class T,typename C1,typename C2> class BASc0m2 : public BAScall0{
public:
	typedef void (T::*F)(C1 c1,C2 c2);
	BASc0m2():_pF(0),_pObj(0){}
	BASc0m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc0m2(){}
	void run() const {(_pObj->*_pF)(_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename C1,typename C2>
inline BASc0m2<T,C1,C2>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2),C1 c1,C2 c2){return new BASc0m2<T,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename C1,typename C2>
inline BASc0m2<T,C1,C2>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2) const,C1 c1,C2 c2){return new BASc0m2<T,C1,C2>(pObj,(void (T::*)(C1,C2))fn,c1,c2);}

template <class T,typename C1,typename C2,typename C3> class BASc0m3 : public BAScall0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3);
	BASc0m3():_pF(0),_pObj(0){}
	BASc0m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc0m3(){}
	void run() const {(_pObj->*_pF)(_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename C1,typename C2,typename C3>
inline BASc0m3<T,C1,C2,C3>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc0m3<T,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename C1,typename C2,typename C3>
inline BASc0m3<T,C1,C2,C3>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc0m3<T,C1,C2,C3>(pObj,(void (T::*)(C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename C1,typename C2,typename C3,typename C4> class BASc0m4 : public BAScall0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3,C4 c4);
	BASc0m4():_pF(0),_pObj(0){}
	BASc0m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc0m4(){}
	void run() const {(_pObj->*_pF)(_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename C1,typename C2,typename C3,typename C4>
inline BASc0m4<T,C1,C2,C3,C4>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc0m4<T,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename C1,typename C2,typename C3,typename C4>
inline BASc0m4<T,C1,C2,C3,C4>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc0m4<T,C1,C2,C3,C4>(pObj,(void (T::*)(C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc0m5 : public BAScall0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc0m5():_pF(0),_pObj(0){}
	BASc0m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc0m5(){}
	void run() const {(_pObj->*_pF)(_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc0m5<T,C1,C2,C3,C4,C5>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc0m5<T,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc0m5<T,C1,C2,C3,C4,C5>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc0m5<T,C1,C2,C3,C4,C5>(pObj,(void (T::*)(C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc0m6 : public BAScall0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc0m6():_pF(0),_pObj(0){}
	BASc0m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc0m6(){}
	void run() const {(_pObj->*_pF)(_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc0m6<T,C1,C2,C3,C4,C5,C6>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc0m6<T,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc0m6<T,C1,C2,C3,C4,C5,C6>* BAScallBind0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc0m6<T,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1> class BASc1m0 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1);
	BASc1m0():_pF(0),_pObj(0){}
	BASc1m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc1m0(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1>
inline BASc1m0<T,A1>* BAScallBind1(T* pObj, void (T::*fn)(A1)){return new BASc1m0<T,A1>(pObj,fn);}

template <class T,typename A1>
inline BASc1m0<T,A1>* BAScallBind1(T* pObj, void (T::*fn)(A1) const){return new BASc1m0<T,A1>(pObj,(void (T::*)(A1))fn);}

template <class T,typename A1,typename C1> class BASc1m1 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1);
	BASc1m1():_pF(0),_pObj(0){}
	BASc1m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc1m1(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename C1>
inline BASc1m1<T,A1,C1>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1),C1 c1){return new BASc1m1<T,A1,C1>(pObj,fn,c1);}

template <class T,typename A1,typename C1>
inline BASc1m1<T,A1,C1>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1) const,C1 c1){return new BASc1m1<T,A1,C1>(pObj,(void (T::*)(A1,C1))fn,c1);}

template <class T,typename A1,typename C1,typename C2> class BASc1m2 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2);
	BASc1m2():_pF(0),_pObj(0){}
	BASc1m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc1m2(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename C1,typename C2>
inline BASc1m2<T,A1,C1,C2>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2),C1 c1,C2 c2){return new BASc1m2<T,A1,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename C1,typename C2>
inline BASc1m2<T,A1,C1,C2>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2) const,C1 c1,C2 c2){return new BASc1m2<T,A1,C1,C2>(pObj,(void (T::*)(A1,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename C1,typename C2,typename C3> class BASc1m3 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3);
	BASc1m3():_pF(0),_pObj(0){}
	BASc1m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc1m3(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename C1,typename C2,typename C3>
inline BASc1m3<T,A1,C1,C2,C3>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc1m3<T,A1,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename C1,typename C2,typename C3>
inline BASc1m3<T,A1,C1,C2,C3>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc1m3<T,A1,C1,C2,C3>(pObj,(void (T::*)(A1,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4> class BASc1m4 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc1m4():_pF(0),_pObj(0){}
	BASc1m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc1m4(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4>
inline BASc1m4<T,A1,C1,C2,C3,C4>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc1m4<T,A1,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4>
inline BASc1m4<T,A1,C1,C2,C3,C4>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc1m4<T,A1,C1,C2,C3,C4>(pObj,(void (T::*)(A1,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc1m5 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc1m5():_pF(0),_pObj(0){}
	BASc1m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc1m5(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc1m5<T,A1,C1,C2,C3,C4,C5>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc1m5<T,A1,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc1m5<T,A1,C1,C2,C3,C4,C5>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc1m5<T,A1,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc1m6 : public BAScall1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc1m6():_pF(0),_pObj(0){}
	BASc1m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc1m6(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc1m6<T,A1,C1,C2,C3,C4,C5,C6>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc1m6<T,A1,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc1m6<T,A1,C1,C2,C3,C4,C5,C6>* BAScallBind1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc1m6<T,A1,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2> class BASc2m0 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2);
	BASc2m0():_pF(0),_pObj(0){}
	BASc2m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc2m0(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2>
inline BASc2m0<T,A1,A2>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2)){return new BASc2m0<T,A1,A2>(pObj,fn);}

template <class T,typename A1,typename A2>
inline BASc2m0<T,A1,A2>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2) const){return new BASc2m0<T,A1,A2>(pObj,(void (T::*)(A1,A2))fn);}

template <class T,typename A1,typename A2,typename C1> class BASc2m1 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1);
	BASc2m1():_pF(0),_pObj(0){}
	BASc2m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc2m1(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename C1>
inline BASc2m1<T,A1,A2,C1>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1),C1 c1){return new BASc2m1<T,A1,A2,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename C1>
inline BASc2m1<T,A1,A2,C1>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1) const,C1 c1){return new BASc2m1<T,A1,A2,C1>(pObj,(void (T::*)(A1,A2,C1))fn,c1);}

template <class T,typename A1,typename A2,typename C1,typename C2> class BASc2m2 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2);
	BASc2m2():_pF(0),_pObj(0){}
	BASc2m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc2m2(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename C1,typename C2>
inline BASc2m2<T,A1,A2,C1,C2>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2),C1 c1,C2 c2){return new BASc2m2<T,A1,A2,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename C1,typename C2>
inline BASc2m2<T,A1,A2,C1,C2>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2) const,C1 c1,C2 c2){return new BASc2m2<T,A1,A2,C1,C2>(pObj,(void (T::*)(A1,A2,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3> class BASc2m3 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3);
	BASc2m3():_pF(0),_pObj(0){}
	BASc2m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc2m3(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3>
inline BASc2m3<T,A1,A2,C1,C2,C3>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc2m3<T,A1,A2,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3>
inline BASc2m3<T,A1,A2,C1,C2,C3>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc2m3<T,A1,A2,C1,C2,C3>(pObj,(void (T::*)(A1,A2,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4> class BASc2m4 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc2m4():_pF(0),_pObj(0){}
	BASc2m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc2m4(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4>
inline BASc2m4<T,A1,A2,C1,C2,C3,C4>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc2m4<T,A1,A2,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4>
inline BASc2m4<T,A1,A2,C1,C2,C3,C4>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc2m4<T,A1,A2,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc2m5 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc2m5():_pF(0),_pObj(0){}
	BASc2m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc2m5(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc2m5<T,A1,A2,C1,C2,C3,C4,C5>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc2m5<T,A1,A2,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc2m5<T,A1,A2,C1,C2,C3,C4,C5>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc2m5<T,A1,A2,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc2m6 : public BAScall2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc2m6():_pF(0),_pObj(0){}
	BASc2m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc2m6(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>* BAScallBind2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3> class BASc3m0 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3);
	BASc3m0():_pF(0),_pObj(0){}
	BASc3m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc3m0(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3>
inline BASc3m0<T,A1,A2,A3>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3)){return new BASc3m0<T,A1,A2,A3>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3>
inline BASc3m0<T,A1,A2,A3>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3) const){return new BASc3m0<T,A1,A2,A3>(pObj,(void (T::*)(A1,A2,A3))fn);}

template <class T,typename A1,typename A2,typename A3,typename C1> class BASc3m1 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1);
	BASc3m1():_pF(0),_pObj(0){}
	BASc3m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc3m1(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename C1>
inline BASc3m1<T,A1,A2,A3,C1>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1),C1 c1){return new BASc3m1<T,A1,A2,A3,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename C1>
inline BASc3m1<T,A1,A2,A3,C1>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1) const,C1 c1){return new BASc3m1<T,A1,A2,A3,C1>(pObj,(void (T::*)(A1,A2,A3,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2> class BASc3m2 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2);
	BASc3m2():_pF(0),_pObj(0){}
	BASc3m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc3m2(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2>
inline BASc3m2<T,A1,A2,A3,C1,C2>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2),C1 c1,C2 c2){return new BASc3m2<T,A1,A2,A3,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2>
inline BASc3m2<T,A1,A2,A3,C1,C2>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2) const,C1 c1,C2 c2){return new BASc3m2<T,A1,A2,A3,C1,C2>(pObj,(void (T::*)(A1,A2,A3,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3> class BASc3m3 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3);
	BASc3m3():_pF(0),_pObj(0){}
	BASc3m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc3m3(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3>
inline BASc3m3<T,A1,A2,A3,C1,C2,C3>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc3m3<T,A1,A2,A3,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3>
inline BASc3m3<T,A1,A2,A3,C1,C2,C3>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc3m3<T,A1,A2,A3,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4> class BASc3m4 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc3m4():_pF(0),_pObj(0){}
	BASc3m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc3m4(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4>
inline BASc3m4<T,A1,A2,A3,C1,C2,C3,C4>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc3m4<T,A1,A2,A3,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4>
inline BASc3m4<T,A1,A2,A3,C1,C2,C3,C4>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc3m4<T,A1,A2,A3,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc3m5 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc3m5():_pF(0),_pObj(0){}
	BASc3m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc3m5(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc3m6 : public BAScall3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc3m6():_pF(0),_pObj(0){}
	BASc3m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc3m6(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>* BAScallBind3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4> class BASc4m0 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4);
	BASc4m0():_pF(0),_pObj(0){}
	BASc4m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc4m0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3,typename A4>
inline BASc4m0<T,A1,A2,A3,A4>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4)){return new BASc4m0<T,A1,A2,A3,A4>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3,typename A4>
inline BASc4m0<T,A1,A2,A3,A4>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4) const){return new BASc4m0<T,A1,A2,A3,A4>(pObj,(void (T::*)(A1,A2,A3,A4))fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1> class BASc4m1 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1);
	BASc4m1():_pF(0),_pObj(0){}
	BASc4m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc4m1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1>
inline BASc4m1<T,A1,A2,A3,A4,C1>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1),C1 c1){return new BASc4m1<T,A1,A2,A3,A4,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1>
inline BASc4m1<T,A1,A2,A3,A4,C1>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1) const,C1 c1){return new BASc4m1<T,A1,A2,A3,A4,C1>(pObj,(void (T::*)(A1,A2,A3,A4,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2> class BASc4m2 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2);
	BASc4m2():_pF(0),_pObj(0){}
	BASc4m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc4m2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2>
inline BASc4m2<T,A1,A2,A3,A4,C1,C2>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2),C1 c1,C2 c2){return new BASc4m2<T,A1,A2,A3,A4,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2>
inline BASc4m2<T,A1,A2,A3,A4,C1,C2>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2) const,C1 c1,C2 c2){return new BASc4m2<T,A1,A2,A3,A4,C1,C2>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3> class BASc4m3 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3);
	BASc4m3():_pF(0),_pObj(0){}
	BASc4m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc4m3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3>
inline BASc4m3<T,A1,A2,A3,A4,C1,C2,C3>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc4m3<T,A1,A2,A3,A4,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3>
inline BASc4m3<T,A1,A2,A3,A4,C1,C2,C3>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc4m3<T,A1,A2,A3,A4,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4> class BASc4m4 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc4m4():_pF(0),_pObj(0){}
	BASc4m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc4m4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4>
inline BASc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4>
inline BASc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc4m5 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc4m5():_pF(0),_pObj(0){}
	BASc4m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc4m5(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc4m6 : public BAScall4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc4m6():_pF(0),_pObj(0){}
	BASc4m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc4m6(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>* BAScallBind4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5> class BASc5m0 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5);
	BASc5m0():_pF(0),_pObj(0){}
	BASc5m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc5m0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5>
inline BASc5m0<T,A1,A2,A3,A4,A5>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5)){return new BASc5m0<T,A1,A2,A3,A4,A5>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5>
inline BASc5m0<T,A1,A2,A3,A4,A5>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5) const){return new BASc5m0<T,A1,A2,A3,A4,A5>(pObj,(void (T::*)(A1,A2,A3,A4,A5))fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1> class BASc5m1 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1);
	BASc5m1():_pF(0),_pObj(0){}
	BASc5m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc5m1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1>
inline BASc5m1<T,A1,A2,A3,A4,A5,C1>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1),C1 c1){return new BASc5m1<T,A1,A2,A3,A4,A5,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1>
inline BASc5m1<T,A1,A2,A3,A4,A5,C1>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1) const,C1 c1){return new BASc5m1<T,A1,A2,A3,A4,A5,C1>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2> class BASc5m2 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2);
	BASc5m2():_pF(0),_pObj(0){}
	BASc5m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc5m2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2>
inline BASc5m2<T,A1,A2,A3,A4,A5,C1,C2>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2),C1 c1,C2 c2){return new BASc5m2<T,A1,A2,A3,A4,A5,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2>
inline BASc5m2<T,A1,A2,A3,A4,A5,C1,C2>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2) const,C1 c1,C2 c2){return new BASc5m2<T,A1,A2,A3,A4,A5,C1,C2>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3> class BASc5m3 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3);
	BASc5m3():_pF(0),_pObj(0){}
	BASc5m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc5m3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3>
inline BASc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3>
inline BASc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4> class BASc5m4 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc5m4():_pF(0),_pObj(0){}
	BASc5m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc5m4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4>
inline BASc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4>
inline BASc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc5m5 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc5m5():_pF(0),_pObj(0){}
	BASc5m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc5m5(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc5m6 : public BAScall5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc5m6():_pF(0),_pObj(0){}
	BASc5m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc5m6(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>* BAScallBind5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6> class BASc6m0 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6);
	BASc6m0():_pF(0),_pObj(0){}
	BASc6m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~BASc6m0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
inline BASc6m0<T,A1,A2,A3,A4,A5,A6>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6)){return new BASc6m0<T,A1,A2,A3,A4,A5,A6>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
inline BASc6m0<T,A1,A2,A3,A4,A5,A6>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6) const){return new BASc6m0<T,A1,A2,A3,A4,A5,A6>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6))fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1> class BASc6m1 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1);
	BASc6m1():_pF(0),_pObj(0){}
	BASc6m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~BASc6m1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1>
inline BASc6m1<T,A1,A2,A3,A4,A5,A6,C1>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1),C1 c1){return new BASc6m1<T,A1,A2,A3,A4,A5,A6,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1>
inline BASc6m1<T,A1,A2,A3,A4,A5,A6,C1>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1) const,C1 c1){return new BASc6m1<T,A1,A2,A3,A4,A5,A6,C1>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2> class BASc6m2 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2);
	BASc6m2():_pF(0),_pObj(0){}
	BASc6m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~BASc6m2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2>
inline BASc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2),C1 c1,C2 c2){return new BASc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2>
inline BASc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2) const,C1 c1,C2 c2){return new BASc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3> class BASc6m3 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3);
	BASc6m3():_pF(0),_pObj(0){}
	BASc6m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~BASc6m3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3>
inline BASc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new BASc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3>
inline BASc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new BASc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4> class BASc6m4 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4);
	BASc6m4():_pF(0),_pObj(0){}
	BASc6m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~BASc6m4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4>
inline BASc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new BASc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4>
inline BASc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new BASc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5> class BASc6m5 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	BASc6m5():_pF(0),_pObj(0){}
	BASc6m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~BASc6m5(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4,_c5);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5>
inline BASc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new BASc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class BASc6m6 : public BAScall6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	BASc6m6():_pF(0),_pObj(0){}
	BASc6m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~BASc6m6(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4,_c5,_c6);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
	C5 _c5;
	C6 _c6;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline BASc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>* BAScallBind6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new BASc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}


/*function ArgList(ArgCount, CapCount)
   local R = ''
   for i=1, ArgCount do
      R=R..'A'..i..' '..'a'..i
      if i<ArgCount then R=R..',' end
   end
   if (ArgCount > 0 and CapCount > 0) then R=R..',' end
   for i=1, CapCount do
      R=R..'C'..i..' '..'c'..i
      if i<CapCount then R=R..',' end
   end
   
   return R
end

function CallList(ArgCount, CapCount)
   local R = ''
   for i=1, ArgCount do
      R=R..'a'..i
      if i<ArgCount then R=R..',' end
   end
   if (ArgCount > 0 and CapCount > 0) then R=R..',' end
   for i=1, CapCount do
      R=R..'c'..i
      if i<CapCount then R=R..',' end
   end
   return R
end

function RunList(ArgCount, CapCount)
   local R = ''
   for i=1, ArgCount do
      R=R..'a'..i
      if i<ArgCount then R=R..',' end
   end
   if (ArgCount > 0 and CapCount > 0) then R=R..',' end
   for i=1, CapCount do
      R=R..'_c'..i
      if i<CapCount then R=R..',' end
   end
   return R
end

function TemplateList(ArgCount,CapCount)
   local R = ''
   for i=1, ArgCount do
      R=R..'A'..i
      if i<ArgCount then R=R..',' end
   end
   if (ArgCount > 0 and CapCount > 0) then R=R..',' end
   for i=1, CapCount do
      R=R..'C'..i
      if i<CapCount then R=R..',' end
   end

   return R   
end

function FunctionCapGen(Arg, CapCount)
   local R = ''
   local Alist = TemplateList(Arg,0)
   for i=0, CapCount do
      local ClassName = "BASc"..Arg..'f'..i
      local TempExpress = TemplateExpression(Arg,i)
      R=R..TempExpress.." class "..ClassName..':public BAScall'..Arg
      if (Arg > 0) then
         R=R..'<'..Alist..'>'
      end
      R=R..'{\n'  
      R=R..'public:\n'
      R=R..'\ttypedef void (*F)('..ArgList(Arg, i)..');\n'
      R=R..'\t'..ClassName..'():_pF(0){}\n'
      local CList = ArgList(0, i)
      local ExtraArgs = ''
      if (i > 0) then ExtraArgs = ','..CList end
      local ArgInit =''
      for j =1, i do
         ArgInit=ArgInit..',_c'..j..'(c'..j..')'
      end
      R=R..'\t'..ClassName..'(F pF'..ExtraArgs..'):_pF(pF)'..ArgInit..'{}\n'
      R=R..'\t~'..ClassName..'(){}\n'
      R=R..'\tvoid run('..ArgList(Arg,0)..') const {(*_pF)('..RunList(Arg,i)..');}\n';
      R=R..'private:\n'
      R=R..'\tF _pF;\n'
      for j=1, i do
         R=R..'\tC'..j..' _c'..j..';\n'
      end
      R=R..'};\n\n'
      local TList = TemplateList(Arg,i)
      local TListD =''
      if #TList > 0 then TListD = '<'..TList..'>' end
      local DecClist = ArgList(0,i)
      if #DecClist > 0 then DecClist=','..DecClist end
      local Clist = CallList(0,i)
      if #Clist > 0 then Clist = ','..Clist end
      R=R..TempExpress..'\ninline '..ClassName..TListD..'* BAScallBind'..Arg..
        '(void (*fn)('..TList..')'..DecClist..'){return new '..ClassName..TListD..'(fn'..Clist..');}\n\n'
   end
   return R
end

function MethodCapGen(Arg, CapCount)
   local R = ''
   local Alist = TemplateList(Arg,0)
   for i=0, CapCount do
      local ClassName = "BASc"..Arg..'m'..i
      local TempExpress = TemplateExpression(Arg,i, true)
      R=R..TempExpress.." class "..ClassName..' : public BAScall'..Arg
      if (Arg > 0) then
         R=R..'<'..Alist..'>'
      end
      R=R..'{\n'  
      R=R..'public:\n'
      R=R..'\ttypedef void (T::*F)('..ArgList(Arg, i)..');\n'
      R=R..'\t'..ClassName..'():_pF(0),_pObj(0){}\n'
      local CList = ArgList(0, i)
      local ExtraArgs = ''
      if (i > 0) then ExtraArgs = ','..CList end
      local ArgInit =''
      for j =1, i do
         ArgInit=ArgInit..',_c'..j..'(c'..j..')'
      end
      R=R..'\t'..ClassName..'(T* pObj,F pF'..ExtraArgs..'):_pObj(pObj),_pF(pF)'..ArgInit..'{}\n'
      R=R..'\t~'..ClassName..'(){}\n'
      R=R..'\tvoid run('..ArgList(Arg,0)..') const {(_pObj->*_pF)('..RunList(Arg,i)..');}\n';
      R=R..'private:\n'
      R=R..'\tT* _pObj;\n'
      R=R..'\tF _pF;\n'
      for j=1, i do
         R=R..'\tC'..j..' _c'..j..';\n'
      end
      R=R..'};\n\n'
      local TList = TemplateList(Arg,i)
      local TListD ='<T>'
      if #TList > 0 then TListD = '<T,'..TList..'>' end
      local DecClist = ArgList(0,i)
      if #DecClist > 0 then DecClist=','..DecClist end
      local Clist = CallList(0,i)
      if #Clist > 0 then Clist = ','..Clist end
      R=R..TempExpress..'\ninline '..ClassName..TListD..'* BAScallBind'..Arg..
        '(T* pObj, void (T::*fn)('..TList..')'..DecClist..'){return new '..ClassName..TListD..'(pObj,fn'..Clist..');}\n\n'
      R=R..TempExpress..'\ninline '..ClassName..TListD..'* BAScallBind'..Arg..
        '(T* pObj, void (T::*fn)('..TList..') const'..DecClist..'){return new '..ClassName..TListD..'(pObj,(void (T::*)('..TList..'))fn'..Clist..');}\n\n'
   end
   return R
end

function TemplateExpression(ArgCount, CapCount, Class)
   local R=''
   if (ArgCount+CapCount > 0 or Class) then 
      R=R..'template <'
      if (Class) then 
         R = R..'class T'
         if (ArgCount + CapCount > 0) then R=R..',' end
      end
      for j=1,ArgCount do
         R=R..'typename A'..j
         if j<ArgCount then R=R..',' end
      end
      if (ArgCount > 0 and CapCount >0) then R=R..',' end
      for j=1,CapCount do
         R=R..'typename C'..j
         if j<CapCount then R=R..',' end
      end
      R=R..'>'
   end
   return R;
end


function ClosureGenerator(ArgCount, CapCount)   
   local R = ''
   for i=0, ArgCount do
      local Args = ArgList(i,0)
      local Alist = CallList(i,0)
      R=R..TemplateExpression(i,0)..'
class BAScall' .. i .."{
"
      R=R..'public:
'
      R=R..'	BAScall'..i..'(){}
'
      R=R..'	virtual ~BAScall'..i..'(){}
'
      R=R..'	virtual void run('..Args..') const=0;
'
      R=R..'	void runAndDelete('..Args..'){run('..Alist..');delete this;}
'
      R=R..'private:
'
      R=R..'	BAScall'..i..'(const BAScall'..i..'& Orig);
'
      R=R..'	BAScall'..i..'& operator=(const BAScall'..i..'& Orig);
'
      R=R..'};

'
   end
   for i=0,ArgCount do
      R=R..FunctionCapGen(i, CapCount)
   end
   for i=0,ArgCount do
      R=R..MethodCapGen(i, CapCount)
   end
   return R
end

Header=[[#pragma once
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  BAScall
//
// Author:  Eliot Muir
//
//
// Description:
//
// A closure takes the leading arguments at run time and captures the trailing
// arguments up front. This is the actual usage pattern:
//
// void BASrunGreeting(BAScall1<const BASstring&>* pCall){
//    pCall->run(BASstring("Greeting"));
// }
//
// void BAShello(const BASstring& Prefix, int Value);
//
// BASrunGreeting(BAScallBind1(&BAShello, 42));
//
// class BASexample {
// public:
//    void print(const BASstring& Prefix, int Value);
// };
//
// BASexample Example;
// BASrunGreeting(BAScallBind1(&Example, &BASexample::print, 99));
// WARNING - this code is generated from a Lua script.  Scroll to the end.
//-----------------------------------------------------------------------------
]]

function main(Data)
   local SelfFName = _G.component.dir()
   local S = io.open(SelfFName.."dev/main.lua", "r");
   local Script = S:read('*a')
   S:close()
   local G = ClosureGenerator(6,6)
   local C = Header..G..'/'..'*'..Script..'*'..'/'
   trace(C)
   local F = io.open('/Users/eliotmuir/main2/COR/BAScallGen.h', 'w')
   F:write(C)
   
end*/
