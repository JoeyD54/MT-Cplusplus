//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef STUDENT4_H
#define STUDENT4_H

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Student4
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
	Student4() = delete;
	Student4(const Student4 &) = delete;
	Student4 &operator = (const Student4 &) = delete;
	~Student4() = default;

	Student4(Name name, int StartValue);

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
