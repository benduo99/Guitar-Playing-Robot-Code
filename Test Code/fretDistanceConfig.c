const float WHEEL_RADIUS = 1.2;
task main()
{
	float distance = 0;
	while(true)
	{
		if(getButtonPress(buttonEnter))
		{
			resetMotorEncoder(motorD);
		}

		while(getButtonPress(buttonRight))
		{
			motor[motorD] = -10;
		}
		motor[motorD] = 0;
		while(getButtonPress(buttonLeft))
		{
			motor[motorD] = 10;
		}
		motor[motorD] = 0;

		distance = nMotorEncoder[motorD] * (2 * PI * WHEEL_RADIUS)/360;
		displayBigTextLine(3, "%f", distance);
	}
}
