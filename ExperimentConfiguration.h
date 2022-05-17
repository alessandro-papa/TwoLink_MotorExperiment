#ifndef CEXPERIMENTCONFIGURATION_H
#define CEXPERIMENTCONFIGURATION_H
#include "Global.h"

constexpr Int32 cCalibrationSamplePeriodMS{20};
constexpr float cCalibrationSamplePeriod{0.02F};
constexpr float cStateEstimationSamplePeriod{0.02F};
constexpr float cFilterSamplePeriod{0.02F};
constexpr float cFilterAlpha{0.98F};
constexpr Int32 cFeedbackSamplePeriodMS{20};
constexpr float cFeedbackSamplePeriod{0.02F};

#endif
