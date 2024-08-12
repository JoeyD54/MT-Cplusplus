//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef STUDENT2_H
#define STUDENT2_H

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Student2
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
	Student2() = delete;
	Student2(const Student2 &) = delete;
	Student2 &operator = (const Student2 &) = delete;
	~Student2() = default;

	Student2(Name name, int StartValue);

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
