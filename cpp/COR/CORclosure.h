#pragma once
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORclosure
//
// Author:  Eliot Muir
//
//
// Description:
//
// A closure takes arguments and it has the ability to capture additional
// variables.  This is an example of the intended usage:
//
// void ServeWebRequest(CORclosure2<int, int>* pClosure){
//    pClosure->run(2,3);
// }
//
// void MakeWebRequest(int ConnectionId, int SequenceId, int* pCount); 
//
// ServeWebRequest(CORnewClosure2<int, int>(&MakeWebRequest, &Count));
// See http://fogbugz.ifware.dynip.com/default.asp?W5842
// WARNING - this code is generated from a Lua script.  Scroll to the end.
//-----------------------------------------------------------------------------

class CORclosure0{
public:
	CORclosure0(){}
	virtual ~CORclosure0(){}
	virtual void run() const=0;
	void runAndDelete(){run();delete this;}
private:
	CORclosure0(const CORclosure0& Orig);
	CORclosure0& operator=(const CORclosure0& Orig);
};

template <typename A1>
class CORclosure1{
public:
	CORclosure1(){}
	virtual ~CORclosure1(){}
	virtual void run(A1 a1) const=0;
	void runAndDelete(A1 a1){run(a1);delete this;}
private:
	CORclosure1(const CORclosure1& Orig);
	CORclosure1& operator=(const CORclosure1& Orig);
};

template <typename A1,typename A2>
class CORclosure2{
public:
	CORclosure2(){}
	virtual ~CORclosure2(){}
	virtual void run(A1 a1,A2 a2) const=0;
	void runAndDelete(A1 a1,A2 a2){run(a1,a2);delete this;}
private:
	CORclosure2(const CORclosure2& Orig);
	CORclosure2& operator=(const CORclosure2& Orig);
};

template <typename A1,typename A2,typename A3>
class CORclosure3{
public:
	CORclosure3(){}
	virtual ~CORclosure3(){}
	virtual void run(A1 a1,A2 a2,A3 a3) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3){run(a1,a2,a3);delete this;}
private:
	CORclosure3(const CORclosure3& Orig);
	CORclosure3& operator=(const CORclosure3& Orig);
};

template <typename A1,typename A2,typename A3,typename A4>
class CORclosure4{
public:
	CORclosure4(){}
	virtual ~CORclosure4(){}
	virtual void run(A1 a1,A2 a2,A3 a3,A4 a4) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3,A4 a4){run(a1,a2,a3,a4);delete this;}
private:
	CORclosure4(const CORclosure4& Orig);
	CORclosure4& operator=(const CORclosure4& Orig);
};

template <typename A1,typename A2,typename A3,typename A4,typename A5>
class CORclosure5{
public:
	CORclosure5(){}
	virtual ~CORclosure5(){}
	virtual void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){run(a1,a2,a3,a4,a5);delete this;}
private:
	CORclosure5(const CORclosure5& Orig);
	CORclosure5& operator=(const CORclosure5& Orig);
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
class CORclosure6{
public:
	CORclosure6(){}
	virtual ~CORclosure6(){}
	virtual void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const=0;
	void runAndDelete(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){run(a1,a2,a3,a4,a5,a6);delete this;}
private:
	CORclosure6(const CORclosure6& Orig);
	CORclosure6& operator=(const CORclosure6& Orig);
};

 class CORc0f0:public CORclosure0{
public:
	typedef void (*F)();
	CORc0f0():_pF(0){}
	CORc0f0(F pF):_pF(pF){}
	~CORc0f0(){}
	void run() const {(*_pF)();}
private:
	F _pF;
};


inline CORc0f0* CORnewClosure0(void (*fn)()){return new CORc0f0(fn);}

template <typename C1> class CORc0f1:public CORclosure0{
public:
	typedef void (*F)(C1 c1);
	CORc0f1():_pF(0){}
	CORc0f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc0f1(){}
	void run() const {(*_pF)(_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename C1>
inline CORc0f1<C1>* CORnewClosure0(void (*fn)(C1),C1 c1){return new CORc0f1<C1>(fn,c1);}

template <typename C1,typename C2> class CORc0f2:public CORclosure0{
public:
	typedef void (*F)(C1 c1,C2 c2);
	CORc0f2():_pF(0){}
	CORc0f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc0f2(){}
	void run() const {(*_pF)(_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename C1,typename C2>
inline CORc0f2<C1,C2>* CORnewClosure0(void (*fn)(C1,C2),C1 c1,C2 c2){return new CORc0f2<C1,C2>(fn,c1,c2);}

template <typename C1,typename C2,typename C3> class CORc0f3:public CORclosure0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3);
	CORc0f3():_pF(0){}
	CORc0f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc0f3(){}
	void run() const {(*_pF)(_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename C1,typename C2,typename C3>
inline CORc0f3<C1,C2,C3>* CORnewClosure0(void (*fn)(C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc0f3<C1,C2,C3>(fn,c1,c2,c3);}

template <typename C1,typename C2,typename C3,typename C4> class CORc0f4:public CORclosure0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3,C4 c4);
	CORc0f4():_pF(0){}
	CORc0f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc0f4(){}
	void run() const {(*_pF)(_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename C1,typename C2,typename C3,typename C4>
inline CORc0f4<C1,C2,C3,C4>* CORnewClosure0(void (*fn)(C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc0f4<C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename C1,typename C2,typename C3,typename C4,typename C5> class CORc0f5:public CORclosure0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc0f5():_pF(0){}
	CORc0f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc0f5(){}
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
inline CORc0f5<C1,C2,C3,C4,C5>* CORnewClosure0(void (*fn)(C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc0f5<C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc0f6:public CORclosure0{
public:
	typedef void (*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc0f6():_pF(0){}
	CORc0f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc0f6(){}
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
inline CORc0f6<C1,C2,C3,C4,C5,C6>* CORnewClosure0(void (*fn)(C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc0f6<C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1> class CORc1f0:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1);
	CORc1f0():_pF(0){}
	CORc1f0(F pF):_pF(pF){}
	~CORc1f0(){}
	void run(A1 a1) const {(*_pF)(a1);}
private:
	F _pF;
};

template <typename A1>
inline CORc1f0<A1>* CORnewClosure1(void (*fn)(A1)){return new CORc1f0<A1>(fn);}

template <typename A1,typename C1> class CORc1f1:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1);
	CORc1f1():_pF(0){}
	CORc1f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc1f1(){}
	void run(A1 a1) const {(*_pF)(a1,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename C1>
inline CORc1f1<A1,C1>* CORnewClosure1(void (*fn)(A1,C1),C1 c1){return new CORc1f1<A1,C1>(fn,c1);}

template <typename A1,typename C1,typename C2> class CORc1f2:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2);
	CORc1f2():_pF(0){}
	CORc1f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc1f2(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename C1,typename C2>
inline CORc1f2<A1,C1,C2>* CORnewClosure1(void (*fn)(A1,C1,C2),C1 c1,C2 c2){return new CORc1f2<A1,C1,C2>(fn,c1,c2);}

template <typename A1,typename C1,typename C2,typename C3> class CORc1f3:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3);
	CORc1f3():_pF(0){}
	CORc1f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc1f3(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename C1,typename C2,typename C3>
inline CORc1f3<A1,C1,C2,C3>* CORnewClosure1(void (*fn)(A1,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc1f3<A1,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename C1,typename C2,typename C3,typename C4> class CORc1f4:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc1f4():_pF(0){}
	CORc1f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc1f4(){}
	void run(A1 a1) const {(*_pF)(a1,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename C1,typename C2,typename C3,typename C4>
inline CORc1f4<A1,C1,C2,C3,C4>* CORnewClosure1(void (*fn)(A1,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc1f4<A1,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc1f5:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc1f5():_pF(0){}
	CORc1f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc1f5(){}
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
inline CORc1f5<A1,C1,C2,C3,C4,C5>* CORnewClosure1(void (*fn)(A1,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc1f5<A1,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc1f6:public CORclosure1<A1>{
public:
	typedef void (*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc1f6():_pF(0){}
	CORc1f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc1f6(){}
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
inline CORc1f6<A1,C1,C2,C3,C4,C5,C6>* CORnewClosure1(void (*fn)(A1,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc1f6<A1,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2> class CORc2f0:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2);
	CORc2f0():_pF(0){}
	CORc2f0(F pF):_pF(pF){}
	~CORc2f0(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2);}
private:
	F _pF;
};

template <typename A1,typename A2>
inline CORc2f0<A1,A2>* CORnewClosure2(void (*fn)(A1,A2)){return new CORc2f0<A1,A2>(fn);}

template <typename A1,typename A2,typename C1> class CORc2f1:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1);
	CORc2f1():_pF(0){}
	CORc2f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc2f1(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename C1>
inline CORc2f1<A1,A2,C1>* CORnewClosure2(void (*fn)(A1,A2,C1),C1 c1){return new CORc2f1<A1,A2,C1>(fn,c1);}

template <typename A1,typename A2,typename C1,typename C2> class CORc2f2:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2);
	CORc2f2():_pF(0){}
	CORc2f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc2f2(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename C1,typename C2>
inline CORc2f2<A1,A2,C1,C2>* CORnewClosure2(void (*fn)(A1,A2,C1,C2),C1 c1,C2 c2){return new CORc2f2<A1,A2,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename C1,typename C2,typename C3> class CORc2f3:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3);
	CORc2f3():_pF(0){}
	CORc2f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc2f3(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename C1,typename C2,typename C3>
inline CORc2f3<A1,A2,C1,C2,C3>* CORnewClosure2(void (*fn)(A1,A2,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc2f3<A1,A2,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4> class CORc2f4:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc2f4():_pF(0){}
	CORc2f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc2f4(){}
	void run(A1 a1,A2 a2) const {(*_pF)(a1,a2,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4>
inline CORc2f4<A1,A2,C1,C2,C3,C4>* CORnewClosure2(void (*fn)(A1,A2,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc2f4<A1,A2,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc2f5:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc2f5():_pF(0){}
	CORc2f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc2f5(){}
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
inline CORc2f5<A1,A2,C1,C2,C3,C4,C5>* CORnewClosure2(void (*fn)(A1,A2,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc2f5<A1,A2,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc2f6:public CORclosure2<A1,A2>{
public:
	typedef void (*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc2f6():_pF(0){}
	CORc2f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc2f6(){}
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
inline CORc2f6<A1,A2,C1,C2,C3,C4,C5,C6>* CORnewClosure2(void (*fn)(A1,A2,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc2f6<A1,A2,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3> class CORc3f0:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3);
	CORc3f0():_pF(0){}
	CORc3f0(F pF):_pF(pF){}
	~CORc3f0(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3>
inline CORc3f0<A1,A2,A3>* CORnewClosure3(void (*fn)(A1,A2,A3)){return new CORc3f0<A1,A2,A3>(fn);}

template <typename A1,typename A2,typename A3,typename C1> class CORc3f1:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1);
	CORc3f1():_pF(0){}
	CORc3f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc3f1(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename C1>
inline CORc3f1<A1,A2,A3,C1>* CORnewClosure3(void (*fn)(A1,A2,A3,C1),C1 c1){return new CORc3f1<A1,A2,A3,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename C1,typename C2> class CORc3f2:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2);
	CORc3f2():_pF(0){}
	CORc3f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc3f2(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2>
inline CORc3f2<A1,A2,A3,C1,C2>* CORnewClosure3(void (*fn)(A1,A2,A3,C1,C2),C1 c1,C2 c2){return new CORc3f2<A1,A2,A3,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3> class CORc3f3:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3);
	CORc3f3():_pF(0){}
	CORc3f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc3f3(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3>
inline CORc3f3<A1,A2,A3,C1,C2,C3>* CORnewClosure3(void (*fn)(A1,A2,A3,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc3f3<A1,A2,A3,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4> class CORc3f4:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc3f4():_pF(0){}
	CORc3f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc3f4(){}
	void run(A1 a1,A2 a2,A3 a3) const {(*_pF)(a1,a2,a3,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4>
inline CORc3f4<A1,A2,A3,C1,C2,C3,C4>* CORnewClosure3(void (*fn)(A1,A2,A3,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc3f4<A1,A2,A3,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc3f5:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc3f5():_pF(0){}
	CORc3f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc3f5(){}
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
inline CORc3f5<A1,A2,A3,C1,C2,C3,C4,C5>* CORnewClosure3(void (*fn)(A1,A2,A3,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc3f5<A1,A2,A3,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc3f6:public CORclosure3<A1,A2,A3>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc3f6():_pF(0){}
	CORc3f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc3f6(){}
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
inline CORc3f6<A1,A2,A3,C1,C2,C3,C4,C5,C6>* CORnewClosure3(void (*fn)(A1,A2,A3,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc3f6<A1,A2,A3,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3,typename A4> class CORc4f0:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4);
	CORc4f0():_pF(0){}
	CORc4f0(F pF):_pF(pF){}
	~CORc4f0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3,typename A4>
inline CORc4f0<A1,A2,A3,A4>* CORnewClosure4(void (*fn)(A1,A2,A3,A4)){return new CORc4f0<A1,A2,A3,A4>(fn);}

template <typename A1,typename A2,typename A3,typename A4,typename C1> class CORc4f1:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1);
	CORc4f1():_pF(0){}
	CORc4f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc4f1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1>
inline CORc4f1<A1,A2,A3,A4,C1>* CORnewClosure4(void (*fn)(A1,A2,A3,A4,C1),C1 c1){return new CORc4f1<A1,A2,A3,A4,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2> class CORc4f2:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2);
	CORc4f2():_pF(0){}
	CORc4f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc4f2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2>
inline CORc4f2<A1,A2,A3,A4,C1,C2>* CORnewClosure4(void (*fn)(A1,A2,A3,A4,C1,C2),C1 c1,C2 c2){return new CORc4f2<A1,A2,A3,A4,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3> class CORc4f3:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3);
	CORc4f3():_pF(0){}
	CORc4f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc4f3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3>
inline CORc4f3<A1,A2,A3,A4,C1,C2,C3>* CORnewClosure4(void (*fn)(A1,A2,A3,A4,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc4f3<A1,A2,A3,A4,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4> class CORc4f4:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc4f4():_pF(0){}
	CORc4f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc4f4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(*_pF)(a1,a2,a3,a4,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4>
inline CORc4f4<A1,A2,A3,A4,C1,C2,C3,C4>* CORnewClosure4(void (*fn)(A1,A2,A3,A4,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc4f4<A1,A2,A3,A4,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc4f5:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc4f5():_pF(0){}
	CORc4f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc4f5(){}
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
inline CORc4f5<A1,A2,A3,A4,C1,C2,C3,C4,C5>* CORnewClosure4(void (*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc4f5<A1,A2,A3,A4,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc4f6:public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc4f6():_pF(0){}
	CORc4f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc4f6(){}
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
inline CORc4f6<A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>* CORnewClosure4(void (*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc4f6<A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3,typename A4,typename A5> class CORc5f0:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5);
	CORc5f0():_pF(0){}
	CORc5f0(F pF):_pF(pF){}
	~CORc5f0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5>
inline CORc5f0<A1,A2,A3,A4,A5>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5)){return new CORc5f0<A1,A2,A3,A4,A5>(fn);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1> class CORc5f1:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1);
	CORc5f1():_pF(0){}
	CORc5f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc5f1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1>
inline CORc5f1<A1,A2,A3,A4,A5,C1>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5,C1),C1 c1){return new CORc5f1<A1,A2,A3,A4,A5,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2> class CORc5f2:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2);
	CORc5f2():_pF(0){}
	CORc5f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc5f2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2>
inline CORc5f2<A1,A2,A3,A4,A5,C1,C2>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5,C1,C2),C1 c1,C2 c2){return new CORc5f2<A1,A2,A3,A4,A5,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3> class CORc5f3:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3);
	CORc5f3():_pF(0){}
	CORc5f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc5f3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3>
inline CORc5f3<A1,A2,A3,A4,A5,C1,C2,C3>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc5f3<A1,A2,A3,A4,A5,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4> class CORc5f4:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc5f4():_pF(0){}
	CORc5f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc5f4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4>
inline CORc5f4<A1,A2,A3,A4,A5,C1,C2,C3,C4>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc5f4<A1,A2,A3,A4,A5,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc5f5:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc5f5():_pF(0){}
	CORc5f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc5f5(){}
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
inline CORc5f5<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc5f5<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc5f6:public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc5f6():_pF(0){}
	CORc5f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc5f6(){}
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
inline CORc5f6<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>* CORnewClosure5(void (*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc5f6<A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6> class CORc6f0:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6);
	CORc6f0():_pF(0){}
	CORc6f0(F pF):_pF(pF){}
	~CORc6f0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6);}
private:
	F _pF;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
inline CORc6f0<A1,A2,A3,A4,A5,A6>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6)){return new CORc6f0<A1,A2,A3,A4,A5,A6>(fn);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1> class CORc6f1:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1);
	CORc6f1():_pF(0){}
	CORc6f1(F pF,C1 c1):_pF(pF),_c1(c1){}
	~CORc6f1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1);}
private:
	F _pF;
	C1 _c1;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1>
inline CORc6f1<A1,A2,A3,A4,A5,A6,C1>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6,C1),C1 c1){return new CORc6f1<A1,A2,A3,A4,A5,A6,C1>(fn,c1);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2> class CORc6f2:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2);
	CORc6f2():_pF(0){}
	CORc6f2(F pF,C1 c1,C2 c2):_pF(pF),_c1(c1),_c2(c2){}
	~CORc6f2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2>
inline CORc6f2<A1,A2,A3,A4,A5,A6,C1,C2>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2),C1 c1,C2 c2){return new CORc6f2<A1,A2,A3,A4,A5,A6,C1,C2>(fn,c1,c2);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3> class CORc6f3:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3);
	CORc6f3():_pF(0){}
	CORc6f3(F pF,C1 c1,C2 c2,C3 c3):_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc6f3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3>
inline CORc6f3<A1,A2,A3,A4,A5,A6,C1,C2,C3>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc6f3<A1,A2,A3,A4,A5,A6,C1,C2,C3>(fn,c1,c2,c3);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4> class CORc6f4:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc6f4():_pF(0){}
	CORc6f4(F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc6f4(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3,_c4);}
private:
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
	C4 _c4;
};

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4>
inline CORc6f4<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc6f4<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>(fn,c1,c2,c3,c4);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc6f5:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc6f5():_pF(0){}
	CORc6f5(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc6f5(){}
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
inline CORc6f5<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc6f5<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>(fn,c1,c2,c3,c4,c5);}

template <typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc6f6:public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc6f6():_pF(0){}
	CORc6f6(F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc6f6(){}
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
inline CORc6f6<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>* CORnewClosure6(void (*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc6f6<A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>(fn,c1,c2,c3,c4,c5,c6);}

template <class T> class CORc0m0 : public CORclosure0{
public:
	typedef void (T::*F)();
	CORc0m0():_pF(0),_pObj(0){}
	CORc0m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc0m0(){}
	void run() const {(_pObj->*_pF)();}
private:
	T* _pObj;
	F _pF;
};

template <class T>
inline CORc0m0<T>* CORnewClosure0(T* pObj, void (T::*fn)()){return new CORc0m0<T>(pObj,fn);}

template <class T>
inline CORc0m0<T>* CORnewClosure0(T* pObj, void (T::*fn)() const){return new CORc0m0<T>(pObj,(void (T::*)())fn);}

template <class T,typename C1> class CORc0m1 : public CORclosure0{
public:
	typedef void (T::*F)(C1 c1);
	CORc0m1():_pF(0),_pObj(0){}
	CORc0m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc0m1(){}
	void run() const {(_pObj->*_pF)(_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename C1>
inline CORc0m1<T,C1>* CORnewClosure0(T* pObj, void (T::*fn)(C1),C1 c1){return new CORc0m1<T,C1>(pObj,fn,c1);}

template <class T,typename C1>
inline CORc0m1<T,C1>* CORnewClosure0(T* pObj, void (T::*fn)(C1) const,C1 c1){return new CORc0m1<T,C1>(pObj,(void (T::*)(C1))fn,c1);}

template <class T,typename C1,typename C2> class CORc0m2 : public CORclosure0{
public:
	typedef void (T::*F)(C1 c1,C2 c2);
	CORc0m2():_pF(0),_pObj(0){}
	CORc0m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc0m2(){}
	void run() const {(_pObj->*_pF)(_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename C1,typename C2>
inline CORc0m2<T,C1,C2>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2),C1 c1,C2 c2){return new CORc0m2<T,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename C1,typename C2>
inline CORc0m2<T,C1,C2>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2) const,C1 c1,C2 c2){return new CORc0m2<T,C1,C2>(pObj,(void (T::*)(C1,C2))fn,c1,c2);}

template <class T,typename C1,typename C2,typename C3> class CORc0m3 : public CORclosure0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3);
	CORc0m3():_pF(0),_pObj(0){}
	CORc0m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc0m3(){}
	void run() const {(_pObj->*_pF)(_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename C1,typename C2,typename C3>
inline CORc0m3<T,C1,C2,C3>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc0m3<T,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename C1,typename C2,typename C3>
inline CORc0m3<T,C1,C2,C3>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc0m3<T,C1,C2,C3>(pObj,(void (T::*)(C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename C1,typename C2,typename C3,typename C4> class CORc0m4 : public CORclosure0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3,C4 c4);
	CORc0m4():_pF(0),_pObj(0){}
	CORc0m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc0m4(){}
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
inline CORc0m4<T,C1,C2,C3,C4>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc0m4<T,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename C1,typename C2,typename C3,typename C4>
inline CORc0m4<T,C1,C2,C3,C4>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc0m4<T,C1,C2,C3,C4>(pObj,(void (T::*)(C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc0m5 : public CORclosure0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc0m5():_pF(0),_pObj(0){}
	CORc0m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc0m5(){}
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
inline CORc0m5<T,C1,C2,C3,C4,C5>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc0m5<T,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc0m5<T,C1,C2,C3,C4,C5>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc0m5<T,C1,C2,C3,C4,C5>(pObj,(void (T::*)(C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc0m6 : public CORclosure0{
public:
	typedef void (T::*F)(C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc0m6():_pF(0),_pObj(0){}
	CORc0m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc0m6(){}
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
inline CORc0m6<T,C1,C2,C3,C4,C5,C6>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc0m6<T,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc0m6<T,C1,C2,C3,C4,C5,C6>* CORnewClosure0(T* pObj, void (T::*fn)(C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc0m6<T,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1> class CORc1m0 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1);
	CORc1m0():_pF(0),_pObj(0){}
	CORc1m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc1m0(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1>
inline CORc1m0<T,A1>* CORnewClosure1(T* pObj, void (T::*fn)(A1)){return new CORc1m0<T,A1>(pObj,fn);}

template <class T,typename A1>
inline CORc1m0<T,A1>* CORnewClosure1(T* pObj, void (T::*fn)(A1) const){return new CORc1m0<T,A1>(pObj,(void (T::*)(A1))fn);}

template <class T,typename A1,typename C1> class CORc1m1 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1);
	CORc1m1():_pF(0),_pObj(0){}
	CORc1m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc1m1(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename C1>
inline CORc1m1<T,A1,C1>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1),C1 c1){return new CORc1m1<T,A1,C1>(pObj,fn,c1);}

template <class T,typename A1,typename C1>
inline CORc1m1<T,A1,C1>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1) const,C1 c1){return new CORc1m1<T,A1,C1>(pObj,(void (T::*)(A1,C1))fn,c1);}

template <class T,typename A1,typename C1,typename C2> class CORc1m2 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2);
	CORc1m2():_pF(0),_pObj(0){}
	CORc1m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc1m2(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename C1,typename C2>
inline CORc1m2<T,A1,C1,C2>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2),C1 c1,C2 c2){return new CORc1m2<T,A1,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename C1,typename C2>
inline CORc1m2<T,A1,C1,C2>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2) const,C1 c1,C2 c2){return new CORc1m2<T,A1,C1,C2>(pObj,(void (T::*)(A1,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename C1,typename C2,typename C3> class CORc1m3 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3);
	CORc1m3():_pF(0),_pObj(0){}
	CORc1m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc1m3(){}
	void run(A1 a1) const {(_pObj->*_pF)(a1,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename C1,typename C2,typename C3>
inline CORc1m3<T,A1,C1,C2,C3>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc1m3<T,A1,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename C1,typename C2,typename C3>
inline CORc1m3<T,A1,C1,C2,C3>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc1m3<T,A1,C1,C2,C3>(pObj,(void (T::*)(A1,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4> class CORc1m4 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc1m4():_pF(0),_pObj(0){}
	CORc1m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc1m4(){}
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
inline CORc1m4<T,A1,C1,C2,C3,C4>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc1m4<T,A1,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4>
inline CORc1m4<T,A1,C1,C2,C3,C4>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc1m4<T,A1,C1,C2,C3,C4>(pObj,(void (T::*)(A1,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc1m5 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc1m5():_pF(0),_pObj(0){}
	CORc1m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc1m5(){}
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
inline CORc1m5<T,A1,C1,C2,C3,C4,C5>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc1m5<T,A1,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc1m5<T,A1,C1,C2,C3,C4,C5>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc1m5<T,A1,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc1m6 : public CORclosure1<A1>{
public:
	typedef void (T::*F)(A1 a1,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc1m6():_pF(0),_pObj(0){}
	CORc1m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc1m6(){}
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
inline CORc1m6<T,A1,C1,C2,C3,C4,C5,C6>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc1m6<T,A1,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc1m6<T,A1,C1,C2,C3,C4,C5,C6>* CORnewClosure1(T* pObj, void (T::*fn)(A1,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc1m6<T,A1,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2> class CORc2m0 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2);
	CORc2m0():_pF(0),_pObj(0){}
	CORc2m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc2m0(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2>
inline CORc2m0<T,A1,A2>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2)){return new CORc2m0<T,A1,A2>(pObj,fn);}

template <class T,typename A1,typename A2>
inline CORc2m0<T,A1,A2>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2) const){return new CORc2m0<T,A1,A2>(pObj,(void (T::*)(A1,A2))fn);}

template <class T,typename A1,typename A2,typename C1> class CORc2m1 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1);
	CORc2m1():_pF(0),_pObj(0){}
	CORc2m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc2m1(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename C1>
inline CORc2m1<T,A1,A2,C1>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1),C1 c1){return new CORc2m1<T,A1,A2,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename C1>
inline CORc2m1<T,A1,A2,C1>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1) const,C1 c1){return new CORc2m1<T,A1,A2,C1>(pObj,(void (T::*)(A1,A2,C1))fn,c1);}

template <class T,typename A1,typename A2,typename C1,typename C2> class CORc2m2 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2);
	CORc2m2():_pF(0),_pObj(0){}
	CORc2m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc2m2(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename C1,typename C2>
inline CORc2m2<T,A1,A2,C1,C2>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2),C1 c1,C2 c2){return new CORc2m2<T,A1,A2,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename C1,typename C2>
inline CORc2m2<T,A1,A2,C1,C2>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2) const,C1 c1,C2 c2){return new CORc2m2<T,A1,A2,C1,C2>(pObj,(void (T::*)(A1,A2,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3> class CORc2m3 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3);
	CORc2m3():_pF(0),_pObj(0){}
	CORc2m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc2m3(){}
	void run(A1 a1,A2 a2) const {(_pObj->*_pF)(a1,a2,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3>
inline CORc2m3<T,A1,A2,C1,C2,C3>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc2m3<T,A1,A2,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3>
inline CORc2m3<T,A1,A2,C1,C2,C3>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc2m3<T,A1,A2,C1,C2,C3>(pObj,(void (T::*)(A1,A2,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4> class CORc2m4 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc2m4():_pF(0),_pObj(0){}
	CORc2m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc2m4(){}
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
inline CORc2m4<T,A1,A2,C1,C2,C3,C4>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc2m4<T,A1,A2,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4>
inline CORc2m4<T,A1,A2,C1,C2,C3,C4>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc2m4<T,A1,A2,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc2m5 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc2m5():_pF(0),_pObj(0){}
	CORc2m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc2m5(){}
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
inline CORc2m5<T,A1,A2,C1,C2,C3,C4,C5>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc2m5<T,A1,A2,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc2m5<T,A1,A2,C1,C2,C3,C4,C5>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc2m5<T,A1,A2,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc2m6 : public CORclosure2<A1,A2>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc2m6():_pF(0),_pObj(0){}
	CORc2m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc2m6(){}
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
inline CORc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>* CORnewClosure2(T* pObj, void (T::*fn)(A1,A2,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc2m6<T,A1,A2,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3> class CORc3m0 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3);
	CORc3m0():_pF(0),_pObj(0){}
	CORc3m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc3m0(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3>
inline CORc3m0<T,A1,A2,A3>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3)){return new CORc3m0<T,A1,A2,A3>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3>
inline CORc3m0<T,A1,A2,A3>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3) const){return new CORc3m0<T,A1,A2,A3>(pObj,(void (T::*)(A1,A2,A3))fn);}

template <class T,typename A1,typename A2,typename A3,typename C1> class CORc3m1 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1);
	CORc3m1():_pF(0),_pObj(0){}
	CORc3m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc3m1(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename C1>
inline CORc3m1<T,A1,A2,A3,C1>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1),C1 c1){return new CORc3m1<T,A1,A2,A3,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename C1>
inline CORc3m1<T,A1,A2,A3,C1>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1) const,C1 c1){return new CORc3m1<T,A1,A2,A3,C1>(pObj,(void (T::*)(A1,A2,A3,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2> class CORc3m2 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2);
	CORc3m2():_pF(0),_pObj(0){}
	CORc3m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc3m2(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2>
inline CORc3m2<T,A1,A2,A3,C1,C2>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2),C1 c1,C2 c2){return new CORc3m2<T,A1,A2,A3,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2>
inline CORc3m2<T,A1,A2,A3,C1,C2>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2) const,C1 c1,C2 c2){return new CORc3m2<T,A1,A2,A3,C1,C2>(pObj,(void (T::*)(A1,A2,A3,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3> class CORc3m3 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3);
	CORc3m3():_pF(0),_pObj(0){}
	CORc3m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc3m3(){}
	void run(A1 a1,A2 a2,A3 a3) const {(_pObj->*_pF)(a1,a2,a3,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3>
inline CORc3m3<T,A1,A2,A3,C1,C2,C3>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc3m3<T,A1,A2,A3,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3>
inline CORc3m3<T,A1,A2,A3,C1,C2,C3>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc3m3<T,A1,A2,A3,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4> class CORc3m4 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc3m4():_pF(0),_pObj(0){}
	CORc3m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc3m4(){}
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
inline CORc3m4<T,A1,A2,A3,C1,C2,C3,C4>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc3m4<T,A1,A2,A3,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4>
inline CORc3m4<T,A1,A2,A3,C1,C2,C3,C4>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc3m4<T,A1,A2,A3,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc3m5 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc3m5():_pF(0),_pObj(0){}
	CORc3m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc3m5(){}
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
inline CORc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc3m5<T,A1,A2,A3,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc3m6 : public CORclosure3<A1,A2,A3>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc3m6():_pF(0),_pObj(0){}
	CORc3m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc3m6(){}
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
inline CORc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>* CORnewClosure3(T* pObj, void (T::*fn)(A1,A2,A3,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc3m6<T,A1,A2,A3,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4> class CORc4m0 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4);
	CORc4m0():_pF(0),_pObj(0){}
	CORc4m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc4m0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3,typename A4>
inline CORc4m0<T,A1,A2,A3,A4>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4)){return new CORc4m0<T,A1,A2,A3,A4>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3,typename A4>
inline CORc4m0<T,A1,A2,A3,A4>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4) const){return new CORc4m0<T,A1,A2,A3,A4>(pObj,(void (T::*)(A1,A2,A3,A4))fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1> class CORc4m1 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1);
	CORc4m1():_pF(0),_pObj(0){}
	CORc4m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc4m1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1>
inline CORc4m1<T,A1,A2,A3,A4,C1>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1),C1 c1){return new CORc4m1<T,A1,A2,A3,A4,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1>
inline CORc4m1<T,A1,A2,A3,A4,C1>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1) const,C1 c1){return new CORc4m1<T,A1,A2,A3,A4,C1>(pObj,(void (T::*)(A1,A2,A3,A4,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2> class CORc4m2 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2);
	CORc4m2():_pF(0),_pObj(0){}
	CORc4m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc4m2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2>
inline CORc4m2<T,A1,A2,A3,A4,C1,C2>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2),C1 c1,C2 c2){return new CORc4m2<T,A1,A2,A3,A4,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2>
inline CORc4m2<T,A1,A2,A3,A4,C1,C2>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2) const,C1 c1,C2 c2){return new CORc4m2<T,A1,A2,A3,A4,C1,C2>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3> class CORc4m3 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3);
	CORc4m3():_pF(0),_pObj(0){}
	CORc4m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc4m3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4) const {(_pObj->*_pF)(a1,a2,a3,a4,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3>
inline CORc4m3<T,A1,A2,A3,A4,C1,C2,C3>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc4m3<T,A1,A2,A3,A4,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3>
inline CORc4m3<T,A1,A2,A3,A4,C1,C2,C3>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc4m3<T,A1,A2,A3,A4,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4> class CORc4m4 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc4m4():_pF(0),_pObj(0){}
	CORc4m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc4m4(){}
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
inline CORc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4>
inline CORc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc4m4<T,A1,A2,A3,A4,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc4m5 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc4m5():_pF(0),_pObj(0){}
	CORc4m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc4m5(){}
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
inline CORc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc4m5<T,A1,A2,A3,A4,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc4m6 : public CORclosure4<A1,A2,A3,A4>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc4m6():_pF(0),_pObj(0){}
	CORc4m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc4m6(){}
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
inline CORc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>* CORnewClosure4(T* pObj, void (T::*fn)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc4m6<T,A1,A2,A3,A4,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,A4,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5> class CORc5m0 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5);
	CORc5m0():_pF(0),_pObj(0){}
	CORc5m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc5m0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5>
inline CORc5m0<T,A1,A2,A3,A4,A5>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5)){return new CORc5m0<T,A1,A2,A3,A4,A5>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5>
inline CORc5m0<T,A1,A2,A3,A4,A5>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5) const){return new CORc5m0<T,A1,A2,A3,A4,A5>(pObj,(void (T::*)(A1,A2,A3,A4,A5))fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1> class CORc5m1 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1);
	CORc5m1():_pF(0),_pObj(0){}
	CORc5m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc5m1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1>
inline CORc5m1<T,A1,A2,A3,A4,A5,C1>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1),C1 c1){return new CORc5m1<T,A1,A2,A3,A4,A5,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1>
inline CORc5m1<T,A1,A2,A3,A4,A5,C1>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1) const,C1 c1){return new CORc5m1<T,A1,A2,A3,A4,A5,C1>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2> class CORc5m2 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2);
	CORc5m2():_pF(0),_pObj(0){}
	CORc5m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc5m2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2>
inline CORc5m2<T,A1,A2,A3,A4,A5,C1,C2>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2),C1 c1,C2 c2){return new CORc5m2<T,A1,A2,A3,A4,A5,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2>
inline CORc5m2<T,A1,A2,A3,A4,A5,C1,C2>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2) const,C1 c1,C2 c2){return new CORc5m2<T,A1,A2,A3,A4,A5,C1,C2>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3> class CORc5m3 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3);
	CORc5m3():_pF(0),_pObj(0){}
	CORc5m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc5m3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3>
inline CORc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3>
inline CORc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc5m3<T,A1,A2,A3,A4,A5,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4> class CORc5m4 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc5m4():_pF(0),_pObj(0){}
	CORc5m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc5m4(){}
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
inline CORc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4>
inline CORc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc5m4<T,A1,A2,A3,A4,A5,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc5m5 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc5m5():_pF(0),_pObj(0){}
	CORc5m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc5m5(){}
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
inline CORc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc5m5<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc5m6 : public CORclosure5<A1,A2,A3,A4,A5>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc5m6():_pF(0),_pObj(0){}
	CORc5m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc5m6(){}
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
inline CORc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>* CORnewClosure5(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc5m6<T,A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,A4,A5,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6> class CORc6m0 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6);
	CORc6m0():_pF(0),_pObj(0){}
	CORc6m0(T* pObj,F pF):_pObj(pObj),_pF(pF){}
	~CORc6m0(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6);}
private:
	T* _pObj;
	F _pF;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
inline CORc6m0<T,A1,A2,A3,A4,A5,A6>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6)){return new CORc6m0<T,A1,A2,A3,A4,A5,A6>(pObj,fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
inline CORc6m0<T,A1,A2,A3,A4,A5,A6>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6) const){return new CORc6m0<T,A1,A2,A3,A4,A5,A6>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6))fn);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1> class CORc6m1 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1);
	CORc6m1():_pF(0),_pObj(0){}
	CORc6m1(T* pObj,F pF,C1 c1):_pObj(pObj),_pF(pF),_c1(c1){}
	~CORc6m1(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1>
inline CORc6m1<T,A1,A2,A3,A4,A5,A6,C1>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1),C1 c1){return new CORc6m1<T,A1,A2,A3,A4,A5,A6,C1>(pObj,fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1>
inline CORc6m1<T,A1,A2,A3,A4,A5,A6,C1>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1) const,C1 c1){return new CORc6m1<T,A1,A2,A3,A4,A5,A6,C1>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1))fn,c1);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2> class CORc6m2 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2);
	CORc6m2():_pF(0),_pObj(0){}
	CORc6m2(T* pObj,F pF,C1 c1,C2 c2):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2){}
	~CORc6m2(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2>
inline CORc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2),C1 c1,C2 c2){return new CORc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>(pObj,fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2>
inline CORc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2) const,C1 c1,C2 c2){return new CORc6m2<T,A1,A2,A3,A4,A5,A6,C1,C2>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2))fn,c1,c2);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3> class CORc6m3 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3);
	CORc6m3():_pF(0),_pObj(0){}
	CORc6m3(T* pObj,F pF,C1 c1,C2 c2,C3 c3):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3){}
	~CORc6m3(){}
	void run(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) const {(_pObj->*_pF)(a1,a2,a3,a4,a5,a6,_c1,_c2,_c3);}
private:
	T* _pObj;
	F _pF;
	C1 _c1;
	C2 _c2;
	C3 _c3;
};

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3>
inline CORc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3),C1 c1,C2 c2,C3 c3){return new CORc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>(pObj,fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3>
inline CORc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3) const,C1 c1,C2 c2,C3 c3){return new CORc6m3<T,A1,A2,A3,A4,A5,A6,C1,C2,C3>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3))fn,c1,c2,c3);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4> class CORc6m4 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4);
	CORc6m4():_pF(0),_pObj(0){}
	CORc6m4(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4){}
	~CORc6m4(){}
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
inline CORc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4),C1 c1,C2 c2,C3 c3,C4 c4){return new CORc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>(pObj,fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4>
inline CORc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4) const,C1 c1,C2 c2,C3 c3,C4 c4){return new CORc6m4<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4))fn,c1,c2,c3,c4);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5> class CORc6m5 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5);
	CORc6m5():_pF(0),_pObj(0){}
	CORc6m5(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5){}
	~CORc6m5(){}
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
inline CORc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>(pObj,fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5>
inline CORc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5){return new CORc6m5<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5))fn,c1,c2,c3,c4,c5);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6> class CORc6m6 : public CORclosure6<A1,A2,A3,A4,A5,A6>{
public:
	typedef void (T::*F)(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6);
	CORc6m6():_pF(0),_pObj(0){}
	CORc6m6(T* pObj,F pF,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6):_pObj(pObj),_pF(pF),_c1(c1),_c2(c2),_c3(c3),_c4(c4),_c5(c5),_c6(c6){}
	~CORc6m6(){}
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
inline CORc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6),C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>(pObj,fn,c1,c2,c3,c4,c5,c6);}

template <class T,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename C1,typename C2,typename C3,typename C4,typename C5,typename C6>
inline CORc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>* CORnewClosure6(T* pObj, void (T::*fn)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6) const,C1 c1,C2 c2,C3 c3,C4 c4,C5 c5,C6 c6){return new CORc6m6<T,A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6>(pObj,(void (T::*)(A1,A2,A3,A4,A5,A6,C1,C2,C3,C4,C5,C6))fn,c1,c2,c3,c4,c5,c6);}

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
      local ClassName = "CORc"..Arg..'f'..i
      local TempExpress = TemplateExpression(Arg,i)
      R=R..TempExpress.." class "..ClassName..':public CORclosure'..Arg
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
      R=R..TempExpress..'\ninline '..ClassName..TListD..'* CORnewClosure'..Arg..
        '(void (*fn)('..TList..')'..DecClist..'){return new '..ClassName..TListD..'(fn'..Clist..');}\n\n'
   end
   return R
end

function MethodCapGen(Arg, CapCount)
   local R = ''
   local Alist = TemplateList(Arg,0)
   for i=0, CapCount do
      local ClassName = "CORc"..Arg..'m'..i
      local TempExpress = TemplateExpression(Arg,i, true)
      R=R..TempExpress.." class "..ClassName..' : public CORclosure'..Arg
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
      R=R..TempExpress..'\ninline '..ClassName..TListD..'* CORnewClosure'..Arg..
        '(T* pObj, void (T::*fn)('..TList..')'..DecClist..'){return new '..ClassName..TListD..'(pObj,fn'..Clist..');}\n\n'
      R=R..TempExpress..'\ninline '..ClassName..TListD..'* CORnewClosure'..Arg..
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
      R=R..TemplateExpression(i,0)..'\nclass CORclosure' .. i .."{\n" 
      R=R..'public:\n'
      R=R..'\tCORclosure'..i..'(){}\n'
      R=R..'\tvirtual ~CORclosure'..i..'(){}\n'
      R=R..'\tvirtual void run('..Args..') const=0;\n'
      R=R..'\tvoid runAndDelete('..Args..'){run('..Alist..');delete this;}\n'
      R=R..'private:\n'
      R=R..'\tCORclosure'..i..'(const CORclosure'..i..'& Orig);\n'
      R=R..'\tCORclosure'..i..'& operator=(const CORclosure'..i..'& Orig);\n'
      R=R..'};\n\n'
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
// Module:  CORclosure
//
// Author:  Eliot Muir
//
//
// Description:
//
// A closure takes arguments and it has the ability to capture additional
// variables.  This is an example of the intended usage:
//
// void ServeWebRequest(CORclosure2<int, int>* pClosure){
//    pClosure->run(2,3);
// }
//
// void MakeWebRequest(int ConnectionId, int SequenceId, int* pCount); 
//
// ServeWebRequest(CORnewClosure2<int, int>(&MakeWebRequest, &Count));
// See http://fogbugz.ifware.dynip.com/default.asp?W5842
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
   local F = io.open('/Users/eliotmuir/main2/COR/CORclosureGen.h', 'w')
   F:write(C)
   
end*/
