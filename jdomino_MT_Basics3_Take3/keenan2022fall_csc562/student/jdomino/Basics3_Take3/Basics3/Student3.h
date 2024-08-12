//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef STUDENT3_H
#define STUDENT3_H

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Student3
{
public:
	enum class Name
	{
		Lisa,
		Jim,
		Mike,
		Jay
	};

public:
	Student3() = delete;
	Student3(const Student3 &) = delete;
	Student3 &operator = (const Student3 &) = delete;
	~Student3() = default;

	Student3(Name name, int StartValue);

	const char *GetName() const;

// -------------------------
//  Data:  add data if needed
// -------------------------
	std::mutex mtx;
	int score;
	Name name;
	
};


#endif

// --- End of File ---
