#include <iostream>   
#include <cstdlib>    
#include <ctime>      
#include "Project  2.h"
using namespace std;

enum enQuestionsLevel { Easy = 1 , Med = 2 , Hard = 3 , MixLevel = 4 };

enum enOperationType { Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , MixOpty = 5 };

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 1;
	
	do 
	{

		cout << " \n How Many Questions Do You Want To Answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);



	return NumberOfQuestions;

}

struct stQuestion {

	short Number1 = 0;
	short Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;

};

struct stQuizz {
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	enOperationType OpType;
	enQuestionsLevel QuesLevel;
	bool isPass = false;
};

short RandomNumber(int from, int to)
{
	short RandNum = rand() % (to - from + 1) + from;

	return RandNum;
}

enQuestionsLevel ReadQuestionLevel() {

	short QuesLevel;

	cout << "Please Enter Questions Level [1] Easy , [2] Med , [3] Hard , [4] Mix : ";
	cin >> QuesLevel;


	return (enQuestionsLevel)QuesLevel;

}

enOperationType ReadOperationType() {

	short OpType;
	do
	{

		cout << "Please Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix : ";
		cin >> OpType;

		
	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;

}

string ChoiceName(enOperationType Choice) {

	string arrGameChoices[5] = { "+" , "-" , "*" , "/" , "mix"};
	return arrGameChoices[Choice - 1];


}

enOperationType GetRandomOperationType()
{
	short OpType = RandomNumber(1, 4);

	return (enOperationType)OpType;

}

int SimpleCalculater(short Number1, short Number2, enOperationType OpType)
{

	if (OpType == enOperationType::Add)
		return Number1 + Number2;
	else if (OpType == enOperationType::Sub)
		return Number1 - Number2;
	else if (OpType == enOperationType::Div)
		return Number1 / Number2;
	else if (OpType == enOperationType::Mul)
		return Number1 * Number2;

	else
		return Number1 + Number2;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OperationType) {

	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::MixLevel)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::MixOpty)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionLevel) {

		case enQuestionsLevel::Easy:
			Question.Number1 = RandomNumber(1, 10);
			Question.Number2 = RandomNumber(1, 10);

			Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
			Question.QuestionLevel = QuestionLevel;
			return Question;

		case enQuestionsLevel::Med:
			Question.Number1 = RandomNumber(10, 50);
			Question.Number2 = RandomNumber(10, 50);

			Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
			Question.QuestionLevel = QuestionLevel;
			return Question;

		case enQuestionsLevel::Hard:
			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);

			Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
			Question.QuestionLevel = QuestionLevel;
			return Question;
	}

}

void GenerateQuizzQuestions(stQuizz& Quizz) {

	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{

		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuesLevel, Quizz.OpType);

	}

}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

void PrintTheQuestion(stQuizz& Quizz, short NumberOfQuestion) {

	cout << "\n\n";
	cout << "Question [" << NumberOfQuestion + 1 << "/" << Quizz.NumberOfQuestions << "] \n";
	cout << Quizz.QuestionList[NumberOfQuestion].Number1;
	cout << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[NumberOfQuestion].OperationType) << " ";
	cout << Quizz.QuestionList[NumberOfQuestion].Number2 << endl;
	cout << "____________________\n";
}

int ReadQustionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;

}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); 
	else
	{
		system("color 4F"); 
		cout << "\a"; 
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short NumberOfQuestion)
{
	if (Quizz.QuestionList[NumberOfQuestion].PlayerAnswer != Quizz.QuestionList[NumberOfQuestion].CorrectAnswer) {

		Quizz.QuestionList[NumberOfQuestion].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer Is : "
	    << Quizz.QuestionList[NumberOfQuestion].CorrectAnswer;
		cout << endl;
	}

	else 
	{  
	Quizz.QuestionList[NumberOfQuestion].AnswerResult = true;
	Quizz.NumberOfRightAnswers++;
	cout << "Right Answer :-) \n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[NumberOfQuestion].AnswerResult);

}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {

	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {

		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQustionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);


}

string GetFinalReslutText(bool Pass) {

	if (Pass)
		return "PASS :-)";
	else
		return "FAIL :-(";

}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel) {

	string ArrQuesLevel[4] = { "Easy", "Med" , "Hard" , "Mix" };
	return ArrQuesLevel[QuestionLevel - 1];
}

void PrintQuizzRestults(stQuizz Quizz) {

	cout << "\n";
	cout << "_______________________________________\n\n";
	cout << "Final Result Is " << GetFinalReslutText(Quizz.isPass);
	cout << "\n________________________________________\n\n";

	cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level     : " << GetQuestionLevelText(Quizz.QuesLevel) << endl;
	cout << "Operation Type      : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers Is : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers Is : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "_________________________________________\n";


}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();

	Quizz.QuesLevel = ReadQuestionLevel();

	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizzRestults(Quizz);


}

string Tabs(short NumberOfTabs) {

	string t = "";

	for (int i = 1; i < NumberOfTabs; i++) {

		t = t + "\t";
		cout << t;
	}

	return t;
}

void ShowFinalResults()
{

	cout << Tabs(2) << "_________________________________________________________\n\n";
	cout << Tabs(2) << "                     +++ G a m e O v e r +++             \n\n";
	cout << Tabs(2) << "_________________________________________________________\n\n";



}

void ResetScreen() {

	system("cls");
	system("color 0F");

}

void StartGame() {

	char PlayAgain = 'Y';
	do
	{
		 ResetScreen();
		 PlayMathGame();

		cout << " \n \t \t Do You Want To Play Again ? Y / N : \n";
		cin >> PlayAgain;


	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main() {

	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}