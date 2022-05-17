#ifndef EEVENT_H
#define EEVENT_H
#include "Global.h"

enum class EEvent : UInt32
{
    DefaultIgnore = 0,
    Init,
    Exit,
    TimerTick,

    /* Communication Events */
    ClientConnected,
    ClientDisconnected,

    /* Data Events */
    ExperimentData,

    /* Experiment Events */
    StopExperiment,
    StartMeasurement,
    StopMeasurement,
    RunE1Calibration,
    RunE2FeedbackControl,
    RunE3ILC,

    /* Control Events */
    EnableController,
    DisableController,
    InSpeedControlArea,
    ReloadConfiguration,
    EnableIntegralFeedback,
    DisableIntegralFeedback,
    EnableOrientationController,
    DisableOrientationController,
    SaveData,
    ToggleOffset,
    /* ILC Events */
    SetupILC,
    CalculateILC,
    ILCExperimentFinished,
    ILCTrialFinished,
	ILCTrialFinishedSoftTransitionEnabled,
    RunILCTrial,
    RunILCDemoTrial,
    ILCExperimentFailed,
    SetNumberOfSamplesPerTrial,
    RunILCExperiment,
    SetNumberOfTrials,
    SetResetPositionAfterTrialFlag,
    EnableSoftTransition,
    DisableSoftTransition,
	SoftTransitionFinished,

    /* QVI Events */
    IterationFinished,
};

#endif
