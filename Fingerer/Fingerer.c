typedef struct
{
	// Fretting Stuff
	tMotor pulleyMotor;
	tSensors touchPort;

	// Strumming Stuff
	tMotor strummingMotor;
	bool isLeft;    // Left relative to motor while looking at it from behind
}Line;

void initializeLine(Line & object, tMotor pulleyMotor, tSensors touchPort, tMotor strummingMotor)
{
	object.pulleyMotor = pulleyMotor;
	object.touchPort = touchPort;
	object.strummingMotor = strummingMotor;
	object.isLeft = true;
}

void strum(Line a, Line g, char currentNote1, char currentNote2)
{
	int parityA = 1;
	int parityB = 1;
	if(!a.isLeft)
	{
		parityA *= -1;
	}
	if(!g.isLeft)
	{
		parityB *= -1;
	}
	if(currentNote1 != '-')
	{
		motor[motorA] = parityA * 70;
		a.isLeft = !a.isLeft;
	}
	if(currentNote2 != '-')
	{
		motor[g.strummingMotor]  = parityB * 70;
		g.isLeft = !g.isLeft;
	}

	while(currentNote1 != '-' && abs(nMotorEncoder[motorA]) > 30 || currentNote2 != '-' && abs(nMotorEncoder[g.strummingMotor]) > 30)
	{

		displayString(0,"%d",nMotorEncoder[motorA]);
		if(abs(nMotorEncoder[motorA]) > 30)
		{
			motor[motorA] = 0;
		}
		if(abs(nMotorEncoder[g.strummingMotor]) > 30)
		{
			motor[g.strummingMotor] = 0;
		}
	}


}


task main()
{
	Line a;
	Line g;

	initializeLine(a, 1, 1, motorA);
	initializeLine(g, 2, 2, motorB);


		while(true)
		{
			while(!getButtonPress(buttonAny))
			{}
			while(getButtonPress(buttonEnter))
			{}
			strum(a, g, 'A', 'A');
	}

}
