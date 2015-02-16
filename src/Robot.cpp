#include "WPILib.h"
#include "JoystickPorts.h"
#include "MainDefines.h"

class Robot: public SampleRobot
{

	LiveWindow *lw;
	RobotDrive robotDrive;
	Joystick leftJoystick;
	Joystick rightJoystick;
	Compressor compressor;
	DoubleSolenoid armSolenoid;

public:

	/**
	 * Robot Constructor
	 * C++ initialization list
	 */
	Robot() :
		lw(NULL),
		robotDrive(LEFT_DRIVE_MOTOR_1, LEFT_DRIVE_MOTOR_2, RIGHT_DRIVE_MOTOR_1, RIGHT_DRIVE_MOTOR_2),
		leftJoystick(LEFT_JOYSTICK_USB_PORT),
		rightJoystick(RIGHT_JOYSTICK_USB_PORT),
		compressor(COMPRESSOR_PORT),
		armSolenoid(ARM_SOLENOID_1, ARM_SOLENOID_2)
	{
		robotDrive.SetExpiration(0.1);
		compressor.Start();
		lw = LiveWindow::GetInstance();
	}

	/**
	 * Autonomous mode
	 */
	void Autonomous()
	{
		Timer autoTimer;
		autoTimer.Start();

		while(IsAutonomous() && IsEnabled()) {
			printf("hello\n");

			int driveSeconds = 2.5;

			if(autoTimer.Get() < driveSeconds) {
				robotDrive.TankDrive(0.5, 0.5);
			}
			else {
				robotDrive.TankDrive(0.0, 0.0);
				autoTimer.Stop();
			}

			Wait(0.05);
		}
	}

	/**
	 * Teleop mode
	 */
	void OperatorControl()
	{
		robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			robotDrive.TankDrive(
				-leftJoystick.GetRawAxis(JoystickPorts::Y_AXIS),
				-rightJoystick.GetRawAxis(JoystickPorts::Y_AXIS)
			);
			ArmControl();
			Wait(0.04);
		} // end while
	}

	void ArmControl() {
		if(BTN_ARM_UP == true) {
			ArmUp();
		}
		else if(BTN_ARM_DOWN == true) {
			ArmDown();
		}
		else {
			ArmSolenoidOff();
		}
	}

	void ArmUp() {
		armSolenoid.Set(DoubleSolenoid::kForward);
	}

	void ArmDown() {
		armSolenoid.Set(DoubleSolenoid::kReverse);
	}

	void ArmSolenoidOff() {
		armSolenoid.Set(DoubleSolenoid::kOff);
	}

	/**
	 * Test mode
	 */
	void Test()
	{
		lw->Run();
		while(IsTest() && IsEnabled()) {
		}
	}
};

START_ROBOT_CLASS(Robot);
