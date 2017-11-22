const float WHEEL_RADIUS = 1.2;
task main()
{
	float distance = 0;
	while(true)
	{
		if(getButtonPress(buttonEnter))
		{
			resetMotorEncoder(motorC);
		}

		while(getButtonPress(buttonRight))
		{
			motor[motorC] = -10;
		}
		motor[motorC] = 0;
		while(getButtonPress(buttonLeft))
		{
			motor[motorC] = 10;
		}
		motor[motorC] = 0;

		distance = nMotorEncoder[motorC] * (2 * PI * WHEEL_RADIUS)/360;
		displayBigTextLine(3, "%f", distance);
	}
}
