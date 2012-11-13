/****************************************************************************
 *
 *  Rohde & Schwarz RTO Digital Oscilloscope instrument driver include file
 *
 ****************************************************************************/

#ifndef __RSSCOPE_HEADER
#define __RSSCOPE_HEADER

#include "rsidr_core.h"
#include "rsscope_attributes.h"
#include "rsscope_utility.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Useful Macros & Constants -----------------------------------------------*
 *****************************************************************************/
#define RSSCOPE_SIMULATION_ID_QUERY      "Rohde&Schwarz,RTO,123456/789,1.23"  /* Default definition of ID Query Response for simulation */
#define RSSCOPE_VALID_ID_RESPONSE_STRING "Rohde&Schwarz"      /* Valid response for identification query */
#define RSSCOPE_SIMULATION_OPT_QUERY     ""      /* Simulated response for *OPT? command */

#define RSSCOPE_IO_BUFFER_SIZE           1024L   /* I/O buffer size */
#define RSSCOPE_OPC_TIMEOUT              5000L   /* Maximum time to wait for OPC in milliseconds */
#define IEEE_488_2_ERROR_MASK             0x4    /* 488.2 STB Bits */   
#define IEEE_488_2_ESE_MASK               0x3D    /* 488.2 Event Status Register (ESE) Bits */
#define RSSCOPE_NAN                 9.91e+37

/****************************************************************************
 *----------------- Instrument Driver Revision Information -----------------*
 ****************************************************************************/

/* Class Driver Identification */

#define RSSCOPE_CLASS_DRIVER_DESCRIPTION           ""
#define RSSCOPE_CLASS_DRIVER_PREFIX                ""
#define RSSCOPE_CLASS_DRIVER_VENDOR                ""
#define RSSCOPE_CLASS_DRIVER_REVISION              ""
#define RSSCOPE_CLASS_SPEC_MAJOR_VERSION           1L    /* Class specification major version */
#define RSSCOPE_CLASS_SPEC_MINOR_VERSION           0L    /* Class specification minor version */

/* Driver Identification */

#define RSSCOPE_SPECIFIC_DRIVER_DESCRIPTION        ""
#define RSSCOPE_SPECIFIC_DRIVER_PREFIX             "RSSCOPE"
#define RSSCOPE_SPECIFIC_DRIVER_LOCATOR            ""
#define RSSCOPE_SPECIFIC_DRIVER_VENDOR             ""
#define RSSCOPE_MAJOR_VERSION                      1L    /* Instrument driver major version          */
#define RSSCOPE_MINOR_VERSION                      40L    /* Instrument driver minor version          */
#define RSSCOPE_MINOR_MINOR_VERSION                1L    /* Instrument driver minor minor version    */

/* Driver Capabilities */          

#define RSSCOPE_SUPPORTED_INSTRUMENT_MODELS        ""    /* Instrument driver supported model(s)     */
#define RSSCOPE_GROUP_CAPABILITIES                 ""
#define RSSCOPE_FUNCTION_CAPABILITIES              ""

/****************************************************************************
 *---------------------------- Attribute Defines ---------------------------*
 ****************************************************************************/

    /*- Inherent Instrument Specific Attributes ----------------------------*/

        /* User Options */

#define RSSCOPE_ATTR_RANGE_CHECK                                           RS_ATTR_RANGE_CHECK                                     /* ViBoolean */
#define RSSCOPE_ATTR_QUERY_INSTRUMENT_STATUS                               RS_ATTR_QUERY_INSTRUMENT_STATUS                         /* ViBoolean */
#define RSSCOPE_ATTR_CACHE                                                 RS_ATTR_CACHE                                           /* ViBoolean */
#define RSSCOPE_ATTR_SIMULATE                                              RS_ATTR_SIMULATE                                        /* ViBoolean */
#define RSSCOPE_ATTR_RECORD_COERCIONS                                      RS_ATTR_RECORD_COERCIONS                                /* ViBoolean */
#define RSSCOPE_ATTR_INTERCHANGE_CHECK                                     RS_ATTR_INTERCHANGE_CHECK                               /* ViBoolean */
#define RSSCOPE_ATTR_SPY                                                   RS_ATTR_SPY                                             /* ViBoolean */
#define RSSCOPE_ATTR_USE_SPECIFIC_SIMULATION                               RS_ATTR_USE_SPECIFIC_SIMULATION                         /* ViBoolean */

        /* Class Driver Identification */

#define RSSCOPE_ATTR_CLASS_DRIVER_DESCRIPTION                              RS_ATTR_CLASS_DRIVER_DESCRIPTION                        /* ViString, read-only */
#define RSSCOPE_ATTR_CLASS_DRIVER_PREFIX                                   RS_ATTR_CLASS_DRIVER_PREFIX                             /* ViString, read-only */
#define RSSCOPE_ATTR_CLASS_DRIVER_VENDOR                                   RS_ATTR_CLASS_DRIVER_VENDOR                             /* ViString, read-only */
#define RSSCOPE_ATTR_CLASS_DRIVER_REVISION                                 RS_ATTR_CLASS_DRIVER_REVISION                           /* ViString, read-only */
#define RSSCOPE_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION                 RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION           /* ViInt32,  read-only */
#define RSSCOPE_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION                 RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION           /* ViInt32,  read-only */

        /* Driver Identification */

#define RSSCOPE_ATTR_SPECIFIC_DRIVER_DESCRIPTION                           RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION                     /* ViString, read-only */
#define RSSCOPE_ATTR_SPECIFIC_DRIVER_PREFIX                                RS_ATTR_SPECIFIC_DRIVER_PREFIX                          /* ViString, read-only */
#define RSSCOPE_ATTR_SPECIFIC_DRIVER_LOCATOR                               RS_ATTR_SPECIFIC_DRIVER_LOCATOR                         /* ViString, read-only */
#define RSSCOPE_ATTR_SPECIFIC_DRIVER_VENDOR                                RS_ATTR_SPECIFIC_DRIVER_VENDOR                          /* ViString, read-only */
#define RSSCOPE_ATTR_SPECIFIC_DRIVER_REVISION                              RS_ATTR_SPECIFIC_DRIVER_REVISION                        /* ViString, read-only */
#define RSSCOPE_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION        /* ViInt32,  read-only */
#define RSSCOPE_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION        /* ViInt32,  read-only */

        /* Driver Capabilities */

#define RSSCOPE_ATTR_SUPPORTED_INSTRUMENT_MODELS                           RS_ATTR_SUPPORTED_INSTRUMENT_MODELS                     /* ViString, read-only */
#define RSSCOPE_ATTR_GROUP_CAPABILITIES                                    RS_ATTR_GROUP_CAPABILITIES                              /* ViString, read-only */
#define RSSCOPE_ATTR_FUNCTION_CAPABILITIES                                 RS_ATTR_FUNCTION_CAPABILITIES                           /* ViString, read-only */
#define RSSCOPE_ATTR_CHANNEL_COUNT                                         RS_ATTR_CHANNEL_COUNT                                   /* ViInt32,  read-only */

        /* Driver Setup */

#define RSSCOPE_ATTR_DRIVER_SETUP                                          RS_ATTR_DRIVER_SETUP                                    /* ViString            */

        /* Instrument Identification */

#define RSSCOPE_ATTR_INSTRUMENT_MANUFACTURER                               RS_ATTR_INSTRUMENT_MANUFACTURER                         /* ViString, read-only */
#define RSSCOPE_ATTR_INSTRUMENT_MODEL                                      RS_ATTR_INSTRUMENT_MODEL                                /* ViString, read-only */
#define RSSCOPE_ATTR_INSTRUMENT_FIRMWARE_REVISION                          RS_ATTR_INSTRUMENT_FIRMWARE_REVISION                    /* ViString, read-only */

        /* Advanced Session Information */

#define RSSCOPE_ATTR_IO_RESOURCE_DESCRIPTOR                                RS_ATTR_IO_RESOURCE_DESCRIPTOR                          /* ViString, read-only */
#define RSSCOPE_ATTR_LOGICAL_NAME                                          RS_ATTR_LOGICAL_NAME

/* ViString, read-only */

    /*- Instrument-Specific Attributes -------------------------------------*/

//#define RSSCOPE_ATTR_ID_QUERY_RESPONSE                                     (RS_SPECIFIC_PUBLIC_ATTR_BASE + 1L)                     /* ViString (Read Only)              */

/* BEGIN GENERATE */
#define RSSCOPE_ATTR_ACQUISITION_TYPE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1
#define RSSCOPE_ATTR_WAVEFORM_ACQUISITION_TYPE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2
#define RSSCOPE_ATTR_INTERPOLATION                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 3
#define RSSCOPE_ATTR_NUM_AVERAGES                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 4
#define RSSCOPE_ATTR_SAMPLE_MODE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 5
#define RSSCOPE_ATTR_HORZ_RECORD_SELECTION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 6
#define RSSCOPE_ATTR_HORZ_TIME_PER_RECORD                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 7
#define RSSCOPE_ATTR_HORZ_RECORD_LENGTH                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 8
#define RSSCOPE_ATTR_HORZ_RECORD_LENGTH_LIMIT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 469
#define RSSCOPE_ATTR_HORZ_SCALE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 9
#define RSSCOPE_ATTR_ACQUSITION_START_TIME                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 10
#define RSSCOPE_ATTR_ACQUISITION_RESTRICT_OFFSET                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 11
#define RSSCOPE_ATTR_ACQUISITION_TIME                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 12
#define RSSCOPE_ATTR_HORZ_SAMPLE_RATE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 13
#define RSSCOPE_ATTR_HORZ_ADC_SAMPLE_RATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 14
#define RSSCOPE_ATTR_AUTOSCALE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 15
#define RSSCOPE_ATTR_HORZ_DIVISIONS                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 16
#define RSSCOPE_ATTR_HORZ_REFERENCE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 17
#define RSSCOPE_ATTR_HORZ_RESOLUTION                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 18
#define RSSCOPE_ATTR_ROLL_MODE_AUTO                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 19
#define RSSCOPE_ATTR_ROLL_MODE_THRESHOLD                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 20
#define RSSCOPE_ATTR_ULTRA_SEGMENTATION_ENABLED                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 21
#define RSSCOPE_ATTR_ULTRA_SEGMENTATION_DEPENDENCY                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 22
#define RSSCOPE_ATTR_ULTRA_SEGMENTATION_AUTO_REPLAY                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 688
#define RSSCOPE_ATTR_CALIBRATION_SOURCE_FREQUENCY                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 309
#define RSSCOPE_ATTR_CALIBRATION_OPERATING_MODE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 310
#define RSSCOPE_ATTR_CALIBRATION_DESTINATION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 311
#define RSSCOPE_ATTR_REF_OSCILLATOR_SOURCE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 470
#define RSSCOPE_ATTR_REF_OSCILLATOR_FREQUENCY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 471
#define RSSCOPE_ATTR_SKEW_OFFSET_STATE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 653
#define RSSCOPE_ATTR_SKEW_OFFSET                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 654
#define RSSCOPE_ATTR_PROBE_STATE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 312
#define RSSCOPE_ATTR_PROBE_TYPE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 313
#define RSSCOPE_ATTR_PROBE_NAME                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 314
#define RSSCOPE_ATTR_PROBE_INPUT_IMPEDANCE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 315
#define RSSCOPE_ATTR_PROBE_INPUT_CAPACITANCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 316
#define RSSCOPE_ATTR_PROBE_ATTENUATION                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 23
#define RSSCOPE_ATTR_PROBE_BANDWIDTH                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 24
#define RSSCOPE_ATTR_PROBE_SET_OFFSET_TO_MEAN                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 317
#define RSSCOPE_ATTR_PROBE_AUTO_ZERO                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 318
#define RSSCOPE_ATTR_PROBE_MICRO_BUTTON_ACTION                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 319
#define RSSCOPE_ATTR_PROBE_MEASUREMENT_TYPE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 574
#define RSSCOPE_ATTR_PROBE_SOFTWARE_VERSION                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 320
#define RSSCOPE_ATTR_PROBE_PRODUCTION_DATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 321
#define RSSCOPE_ATTR_PROBE_PART_NUMBER                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 322
#define RSSCOPE_ATTR_PROBE_SERIAL_NUMBER                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 323
#define RSSCOPE_ATTR_PROBE_FIRMWARE_PATH                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 324
#define RSSCOPE_ATTR_PROBE_FIRMWARE_UPDATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 325
#define RSSCOPE_ATTR_PROBE_FIRMWARE_UPDATE_STATUS                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 326
#define RSSCOPE_ATTR_PROBE_SELFTEST                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 327
#define RSSCOPE_ATTR_PROBE_SELFTEST_STATUS                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 329
#define RSSCOPE_ATTR_PROBE_DETECTION_MODE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 472
#define RSSCOPE_ATTR_PROBE_ATTENUATION_MANUAL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 473
#define RSSCOPE_ATTR_PROBE_VERTICAL_UNIT                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 474
#define RSSCOPE_ATTR_PROBE_GAIN_MANUAL                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 575
#define RSSCOPE_ATTR_PROBE_PREDEFINED_CURRENT_PROBE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 573
#define RSSCOPE_ATTR_CHANNEL_ENABLED                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 25
#define RSSCOPE_ATTR_VERTICAL_RANGE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 26
#define RSSCOPE_ATTR_VERTICAL_OFFSET                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 27
#define RSSCOPE_ATTR_VERTICAL_COUPLING                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 28
#define RSSCOPE_ATTR_VERTICAL_SCALE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 29
#define RSSCOPE_ATTR_CHANNEL_OFFSET                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 30
#define RSSCOPE_ATTR_CHANNEL_BANDWIDTH_LIMIT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 31
#define RSSCOPE_ATTR_CHANNEL_OVERLOAD                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 32
#define RSSCOPE_ATTR_CHANNEL_SKEW                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 33
#define RSSCOPE_ATTR_CHANNEL_THRESHOLD                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 34
#define RSSCOPE_ATTR_INPUT_IMPEDANCE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 35
#define RSSCOPE_ATTR_GROUND_CONNECTION_ENABLED                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 36
#define RSSCOPE_ATTR_DIGITAL_FILTER_STATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 475
#define RSSCOPE_ATTR_DIGITAL_FILTER_CUT_OFF                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 476
#define RSSCOPE_ATTR_DIGITAL_FILTER_TRIGGER_COUPLING                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 477
#define RSSCOPE_ATTR_DIGITAL_FILTER_TRIGGER_RF_REJECT                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 478
#define RSSCOPE_ATTR_EXTERNAL_ATTENUATION_SCALE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 479
#define RSSCOPE_ATTR_EXTERNAL_ATTENUATION_VALUE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 480
#define RSSCOPE_ATTR_TRIGGER_TYPE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 37
#define RSSCOPE_ATTR_TRIGGER_SOURCE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 38
#define RSSCOPE_ATTR_TRIGGER_LEVEL                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 39
#define RSSCOPE_ATTR_TRIGGER_MODIFIER                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 40
#define RSSCOPE_ATTR_TRIGGER_LEVEL_AUTO_FIND                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 41
#define RSSCOPE_ATTR_ROBUST_TRIGGER_STATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 576
#define RSSCOPE_ATTR_TRIGGER_EVENT_COUPLING                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 42
#define RSSCOPE_ATTR_TRIGGER_SOURCE_COUPLING                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 43
#define RSSCOPE_ATTR_TRIGGER_LINES_DISPLAY                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 330
#define RSSCOPE_ATTR_TRIGGER_OUT_STATE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 546
#define RSSCOPE_ATTR_TRIGGER_OUT_POLARITY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 547
#define RSSCOPE_ATTR_TRIGGER_OUT_PULSE_LENGTH                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 548
#define RSSCOPE_ATTR_TRIGGER_OUT_DELAY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 549
#define RSSCOPE_ATTR_EXTERNAL_TRIGGER_COUPLING                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 44
#define RSSCOPE_ATTR_TRIGGER_SLOPE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 45
#define RSSCOPE_ATTR_EXTERNAL_TRIGGER_LEVEL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 46
#define RSSCOPE_ATTR_EXTERNAL_TRIGGER_FILTER_CUT_OFF_FREQENCY               RS_SPECIFIC_PUBLIC_ATTR_BASE + 47
#define RSSCOPE_ATTR_EXTERNAL_TRIGGER_FILTER                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 48
#define RSSCOPE_ATTR_EXTERNAL_TRIGGER_GROUND_CONNECTION_ENABLED             RS_SPECIFIC_PUBLIC_ATTR_BASE + 49
#define RSSCOPE_ATTR_EXTERNAL_TRIGGER_SLOPE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 50
#define RSSCOPE_ATTR_RUNT_HIGH_THRESHOLD                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 54
#define RSSCOPE_ATTR_RUNT_LOW_THRESHOLD                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 55
#define RSSCOPE_ATTR_RUNT_CONDITION                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 56
#define RSSCOPE_ATTR_RUNT_WIDTH                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 57
#define RSSCOPE_ATTR_RUNT_DELTA                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 58
#define RSSCOPE_ATTR_RUNT_POLARITY                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 59
#define RSSCOPE_ATTR_GLITCH_WIDTH                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 60
#define RSSCOPE_ATTR_GLITCH_POLARITY                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 61
#define RSSCOPE_ATTR_GLITCH_CONDITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 62
#define RSSCOPE_ATTR_WIDTH_CONDITION                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 63
#define RSSCOPE_ATTR_WIDTH                                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 64
#define RSSCOPE_ATTR_WIDTH_DELTA                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 65
#define RSSCOPE_ATTR_WIDTH_POLARITY                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 66
#define RSSCOPE_ATTR_WINDOW_UPPER_LIMIT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 67
#define RSSCOPE_ATTR_WINDOW_LOWER_LIMIT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 68
#define RSSCOPE_ATTR_WINDOW_CONDITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 69
#define RSSCOPE_ATTR_WINDOW_WIDTH                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 70
#define RSSCOPE_ATTR_WINDOW_DELTA                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 71
#define RSSCOPE_ATTR_TIMEOUT_CONDITION                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 72
#define RSSCOPE_ATTR_TIMEOUT_VALUE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 73
#define RSSCOPE_ATTR_INTERVAL_CONDITION                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 74
#define RSSCOPE_ATTR_INTERVAL_WIDTH                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 75
#define RSSCOPE_ATTR_INTERVAL_DELTA                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 76
#define RSSCOPE_ATTR_INTERVAL_POLARITY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 77
#define RSSCOPE_ATTR_SLEW_UPPER_LIMIT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 78
#define RSSCOPE_ATTR_SLEW_LOWER_LIMIT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 79
#define RSSCOPE_ATTR_SLEW_CONDITION                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 80
#define RSSCOPE_ATTR_SLEW_RATE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 81
#define RSSCOPE_ATTR_SLEW_DELTA                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 82
#define RSSCOPE_ATTR_SLEW_POLARITY                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 83
#define RSSCOPE_ATTR_DATA2CLOCK_SOURCE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 84
#define RSSCOPE_ATTR_DATA2CLOCK_LEVEL                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 85
#define RSSCOPE_ATTR_DATA2CLOCK_HOLD_TIME                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 86
#define RSSCOPE_ATTR_DATA2CLOCK_SETUP_TIME                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 87
#define RSSCOPE_ATTR_DATA2CLOCK_POLARITY                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 88
#define RSSCOPE_ATTR_PATTERN_MODE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 89
#define RSSCOPE_ATTR_PATTERN_TIMEOUT_MODE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 90
#define RSSCOPE_ATTR_PATTERN_TIMEOUT                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 91
#define RSSCOPE_ATTR_PATTERN_CONDITION                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 92
#define RSSCOPE_ATTR_PATTERN_WIDTH                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 93
#define RSSCOPE_ATTR_PATTERN_DELTA                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 94
#define RSSCOPE_ATTR_SERIAL_PATTERN_SOURCE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 95
#define RSSCOPE_ATTR_SERIAL_PATTERN_LEVEL                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 96
#define RSSCOPE_ATTR_SERIAL_PATTERN                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 97
#define RSSCOPE_ATTR_SERIAL_PATTERN_POLARITY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 98
#define RSSCOPE_ATTR_CHANNEL_PATTERN_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 99
#define RSSCOPE_ATTR_CHANNEL_PATTERN_COMBINATION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 100
#define RSSCOPE_ATTR_CHANNEL_PATTERN_CONDITION                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 101
#define RSSCOPE_ATTR_NFC_TRIGGER_TECHNOLOGY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 665
#define RSSCOPE_ATTR_NFC_TRIGGER_BIT_RATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 666
#define RSSCOPE_ATTR_NFC_TRIGGER_EVENT                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 667
#define RSSCOPE_ATTR_TV_TRIGGER_STANDARD                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 689
#define RSSCOPE_ATTR_TV_TRIGGER_MODE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 690
#define RSSCOPE_ATTR_TV_TRIGGER_LINE_NUMBER                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 52
#define RSSCOPE_ATTR_TV_TRIGGER_FIELD                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 691
#define RSSCOPE_ATTR_TV_TRIGGER_POLARITY                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 53
#define RSSCOPE_ATTR_TV_TRIGGER_PULSE_TYPE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 692
#define RSSCOPE_ATTR_TV_TRIGGER_LINE_PERIOD                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 693
#define RSSCOPE_ATTR_TV_TRIGGER_PULSE_WIDTH                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 694
#define RSSCOPE_ATTR_TV_TRIGGER_SCAN_MODE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 695
#define RSSCOPE_ATTR_TV_TRIGGER_EVENT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 51
#define RSSCOPE_ATTR_B_TRIGGER_ENABLED                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 102
#define RSSCOPE_ATTR_B_TRIGGER_SOURCE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 103
#define RSSCOPE_ATTR_B_TRIGGER_SLOPE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 104
#define RSSCOPE_ATTR_B_TRIGGER_LEVEL                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 105
#define RSSCOPE_ATTR_B_TRIGGER_DELAY_TYPE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 106
#define RSSCOPE_ATTR_B_TRIGGER_HOLDOFF                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 107
#define RSSCOPE_ATTR_B_TRIGGER_EVENT_COUNT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 108
#define RSSCOPE_ATTR_TRIGGER_QUALIFICATION_ENABLED                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 109
#define RSSCOPE_ATTR_TRIGGER_QUALIFICATION_CHANNEL_ENABLED                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 110
#define RSSCOPE_ATTR_TRIGGER_QUALIFICATION_LOGIC                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 111
#define RSSCOPE_ATTR_TRIGGER_QUALIFICATION_MULTICHANNEL_LOGIC               RS_SPECIFIC_PUBLIC_ATTR_BASE + 112
#define RSSCOPE_ATTR_NOISE_REJECT_HYSTERESIS_MODE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 113
#define RSSCOPE_ATTR_NOISE_REJECT_HYSTERESIS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 114
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_MODE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 115
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_MODE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 116
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_TIME                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 117
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_EVENTS                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 118
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_RANDOM_MINIMUM_TIME           RS_SPECIFIC_PUBLIC_ATTR_BASE + 119
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_RANDOM_MAXIMUM_TIME           RS_SPECIFIC_PUBLIC_ATTR_BASE + 120
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_AUTO_TIME_RESULT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 121
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_HOLDOFF_AUTO_SCALE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 122
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_DELAY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 123
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_B_EVENTS_COUNT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 124
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_RESET_BY_TIMEOUT_ENABLED              RS_SPECIFIC_PUBLIC_ATTR_BASE + 125
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_RESET_TIMEOUT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 126
#define RSSCOPE_ATTR_TRIGGER_SEQUENCE_RESET_EVENT_ENABLED                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 127
#define RSSCOPE_ATTR_WAVEFORM_STATE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 128
#define RSSCOPE_ATTR_WAVEFORM_HEADER                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 129
#define RSSCOPE_ATTR_RUN_SINGLE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 130
#define RSSCOPE_ATTR_RUN_CONTINUOUS                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 131
#define RSSCOPE_ATTR_STOP                                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 132
#define RSSCOPE_ATTR_FORCE                                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 133
#define RSSCOPE_ATTR_SEND_SW_TRIGGER                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 134
#define RSSCOPE_ATTR_SEND_SW_TRIGGER_AND_WAIT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 135
#define RSSCOPE_ATTR_MEASUREMENT_ENABLED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 136
#define RSSCOPE_ATTR_MULTIPLE_MEASUREMENT_ENABLED                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 137
#define RSSCOPE_ATTR_MULTIPLE_MEASUREMENT_COUNT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 577
#define RSSCOPE_ATTR_MEASUREMENT_CATEGORY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 138
#define RSSCOPE_ATTR_ADDITIONAL_MEASUREMENTS_ENABLE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 139
#define RSSCOPE_ATTR_ADDITIONAL_MEASUREMENTS_DISABLE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 140
#define RSSCOPE_ATTR_CLEAR_MEASUREMENT_STATISTIC_DATA                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 141
#define RSSCOPE_ATTR_MEASUREMENT_LIMIT_TYPE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 142
#define RSSCOPE_ATTR_MEASUREMENT_DISPLAY_STYLE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 331
#define RSSCOPE_ATTR_GENERATE_BEEP_ON_MEASUREMENT_EVENT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 143
#define RSSCOPE_ATTR_STOP_ACQUISITION_ON_MEASUREMENT_EVENT                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 144
#define RSSCOPE_ATTR_PRINT_ON_MEASUREMENT_EVENT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 145
#define RSSCOPE_ATTR_SAVE_WAVEFORM_DATA_ON_MEASUREMENT_EVENT                RS_SPECIFIC_PUBLIC_ATTR_BASE + 146
#define RSSCOPE_ATTR_AMPT_MAIN_MEASUREMENT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 147
#define RSSCOPE_ATTR_AMPT_AREA_LEVEL                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 148
#define RSSCOPE_ATTR_AMPT_SIGNAL_DETECTION_THRESHOLD                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 149
#define RSSCOPE_ATTR_AMPT_SLOPE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 578
#define RSSCOPE_ATTR_AMPT_DELAY_LEVEL_SELECTION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 579
#define RSSCOPE_ATTR_AMPT_DELAY_SLOPE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 580
#define RSSCOPE_ATTR_AMPT_DELAY_DIRECTION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 581
#define RSSCOPE_ATTR_AMPT_DELAY_EDGE_NUMBER                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 582
#define RSSCOPE_ATTR_AMPT_REFERENCE_LEVEL                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 655
#define RSSCOPE_ATTR_AMPT_LIMIT_CHECK                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 150
#define RSSCOPE_ATTR_AMPT_LIMIT_VALUE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 151
#define RSSCOPE_ATTR_AMPT_LIMIT_MARGIN                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 152
#define RSSCOPE_ATTR_AMPT_PULSE_TRAIN_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 481
#define RSSCOPE_ATTR_ENVELOPE_SELECTION                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 550
#define RSSCOPE_ATTR_EYE_MAIN_MEASUREMENT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 153
#define RSSCOPE_ATTR_EYE_LIMIT_CHECK                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 154
#define RSSCOPE_ATTR_EYE_LIMIT_VALUE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 155
#define RSSCOPE_ATTR_EYE_LIMIT_MARGIN                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 156
#define RSSCOPE_ATTR_HISTOGRAM_MAIN_MEASUREMENT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 157
#define RSSCOPE_ATTR_HISTOGRAM_SELECT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 158
#define RSSCOPE_ATTR_HISTOGRAM_PROBABILITY_TYPE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 159
#define RSSCOPE_ATTR_HISTOGRAM_PROBABILITY_LIMIT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 160
#define RSSCOPE_ATTR_HISTOGRAM_LIMIT_CHECK                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 161
#define RSSCOPE_ATTR_HISTOGRAM_LIMIT_VALUE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 162
#define RSSCOPE_ATTR_HISTOGRAM_LIMIT_MARGIN                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 163
#define RSSCOPE_ATTR_REMOVE_HISTOGRAM                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 332
#define RSSCOPE_ATTR_RESET_HISTOGRAM                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 333
#define RSSCOPE_ATTR_HISTOGRAM_DISPLAY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 334
#define RSSCOPE_ATTR_SPECTRUM_MAIN_MEASUREMENT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 164
#define RSSCOPE_ATTR_SPECTRUM_CHANNEL_POWER_BANDWIDTH                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 165
#define RSSCOPE_ATTR_SPECTRUM_OCCUPIED_BANDWIDTH                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 166
#define RSSCOPE_ATTR_SPECTRUM_CHANNEL_POWER_CENTER_FREQUENCY                RS_SPECIFIC_PUBLIC_ATTR_BASE + 167
#define RSSCOPE_ATTR_SPECTRUM_N_DB_DOWN                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 168
#define RSSCOPE_ATTR_SPECTRUM_NOISE_REJECT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 169
#define RSSCOPE_ATTR_SPECTRUM_LIMIT_CHECK                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 170
#define RSSCOPE_ATTR_SPECTRUM_LIMIT_VALUE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 171
#define RSSCOPE_ATTR_SPECTRUM_LIMIT_MARGIN                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 172
#define RSSCOPE_ATTR_CURSOR_ENABLED                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 173
#define RSSCOPE_ATTR_ALL_CURSORS_OFF                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 174
#define RSSCOPE_ATTR_CURSOR_MEASUREMENT_TYPE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 175
#define RSSCOPE_ATTR_CURSOR_SOURCE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 176
#define RSSCOPE_ATTR_CURSOR_TRACKING                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 177
#define RSSCOPE_ATTR_CURSOR_X_POSITION                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 178
#define RSSCOPE_ATTR_CURSOR_X_POSITION_COUPLING                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 179
#define RSSCOPE_ATTR_CURSOR_Y_POSITION                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 180
#define RSSCOPE_ATTR_CURSOR_Y_POSITION_COUPLING                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 181
#define RSSCOPE_ATTR_CURSOR_ENVELOPE_CURVE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 182
#define RSSCOPE_ATTR_CURSOR_DISTANCE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 183
#define RSSCOPE_ATTR_CURSOR_INVERSE_DISTANCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 184
#define RSSCOPE_ATTR_CURSOR_SEARCH                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 185
#define RSSCOPE_ATTR_CURSOR_PEAK_EXCURSION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 186
#define RSSCOPE_ATTR_CURSOR_X_RATIO_MEASUREMENT_UNIT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 187
#define RSSCOPE_ATTR_CURSOR_X_RATIO_MEASUREMENT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 188
#define RSSCOPE_ATTR_CURSOR_Y_RATIO_MEASUREMENT_UNIT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 189
#define RSSCOPE_ATTR_CURSOR_Y_RATIO_MEASUREMENT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 190
#define RSSCOPE_ATTR_STATISTICS_ENABLED                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 191
#define RSSCOPE_ATTR_STATISTICS_HISTOGRAM_ENABLED                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 656
#define RSSCOPE_ATTR_STATISTICS_RESET_MODE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 192
#define RSSCOPE_ATTR_STATISTICS_RESET_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 193
#define RSSCOPE_ATTR_STATISTICS_RESET_TIME                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 194
#define RSSCOPE_ATTR_STATISTICS_RESET                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 195
#define RSSCOPE_ATTR_STATISTICS_WEIGHT                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 196
#define RSSCOPE_ATTR_LONG_TERM_MEASUREMENT_ENABLED                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 197
#define RSSCOPE_ATTR_LONG_TERM_COUNT                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 198
#define RSSCOPE_ATTR_LONG_TERM_DURATION                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 199
#define RSSCOPE_ATTR_LONG_TERM_VERTICAL_OFFSET                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 200
#define RSSCOPE_ATTR_LONG_TERM_VERTICAL_SCALING                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 201
#define RSSCOPE_ATTR_LONG_TERM_VERTICAL_AUTOSCALE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 202
#define RSSCOPE_ATTR_LONG_TERM_ENVIRONMENT_SENSOR_ENABLED                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 203
#define RSSCOPE_ATTR_GATING_ENABLED                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 204
#define RSSCOPE_ATTR_GATING_MODE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 205
#define RSSCOPE_ATTR_GATING_START                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 206
#define RSSCOPE_ATTR_GATING_STOP                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 207
#define RSSCOPE_ATTR_GATING_NOISE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 208
#define RSSCOPE_ATTR_GATING_SHOW_GATE_AREA                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 209
#define RSSCOPE_ATTR_GATING_ZOOM_COUPLING_ENABLED                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 210
#define RSSCOPE_ATTR_REFERENCE_LEVEL_DISPLAY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 335
#define RSSCOPE_ATTR_REFERENCE_LEVEL_MODE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 211
#define RSSCOPE_ATTR_REFERENCE_LEVEL_RELATIVE_LEVELS                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 212
#define RSSCOPE_ATTR_REFERENCE_LEVEL_USER_LEVEL                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 213
#define RSSCOPE_ATTR_REFERENCE_LEVEL_DEFINITION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 214
#define RSSCOPE_ATTR_REFERENCE_LEVEL_AUTO_MODE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 215
#define RSSCOPE_ATTR_REFERENCE_LEVEL_AVERAGING_ENABLED                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 216
#define RSSCOPE_ATTR_REFERENCE_LEVEL_AVERAGING_COUNT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 217
#define RSSCOPE_ATTR_REFERENCE_USER_SIGNAL_HIGH                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 218
#define RSSCOPE_ATTR_REFERENCE_USER_SIGNAL_LOW                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 219
#define RSSCOPE_ATTR_REFERENCE_USER_TOP_DISTANCE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 220
#define RSSCOPE_ATTR_REFERENCE_USER_BOTTOM_DISTANCE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 221
#define RSSCOPE_ATTR_USER_REFERENCE_UPPER_LEVEL                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 222
#define RSSCOPE_ATTR_USER_REFERENCE_LOWER_LEVEL                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 223
#define RSSCOPE_ATTR_USER_REFERENCE_MIDDLE_LEVEL                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 224
#define RSSCOPE_ATTR_USER_REFERENCE_RELATIVE_UPPER_LEVEL                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 543
#define RSSCOPE_ATTR_USER_REFERENCE_RELATIVE_MIDDLE_LEVEL                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 544
#define RSSCOPE_ATTR_USER_REFERENCE_RELATIVE_LOWER_LEVEL                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 545
#define RSSCOPE_ATTR_USER_REFERENCE_HYSTERESIS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 225
#define RSSCOPE_ATTR_TUBE_RELATIVE_OUTER_DISTANCE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 226
#define RSSCOPE_ATTR_TUBE_RELATIVE_INNER_DISTANCE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 227
#define RSSCOPE_ATTR_TUBE_ABSOLUTE_OUTER_DISTANCE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 228
#define RSSCOPE_ATTR_MAIN_MEASUREMENT_RESULT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 229
#define RSSCOPE_ATTR_AMPT_MEASUREMENT_RESULT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 230
#define RSSCOPE_ATTR_EYE_MEASUREMENT_RESULT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 231
#define RSSCOPE_ATTR_HISTOGRAM_MEASUREMENT_RESULT                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 232
#define RSSCOPE_ATTR_SPECTRUM_MEASUREMENT_RESULT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 233
#define RSSCOPE_ATTR_DISPLAY_RESULT_LINES                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 336
#define RSSCOPE_ATTR_REFERENCE_LEVEL_RESULT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 234
#define RSSCOPE_ATTR_MATH_WAVEFORM_ENABLED                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 235
#define RSSCOPE_ATTR_MATH_ACQUISITION_TYPE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 236
#define RSSCOPE_ATTR_MATH_EXPRESSION                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 237
#define RSSCOPE_ATTR_MATH_VERTICAL_RANGE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 238
#define RSSCOPE_ATTR_MATH_VERTICAL_SCALE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 239
#define RSSCOPE_ATTR_MATH_VERTICAL_OFFSET                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 240
#define RSSCOPE_ATTR_MATH_RESET                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 668
#define RSSCOPE_ATTR_MATH_RESET_MODE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 669
#define RSSCOPE_ATTR_MATH_ENVELOPE_TIMEOUT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 670
#define RSSCOPE_ATTR_MATH_ACQUIRED_WAVEFORMS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 671
#define RSSCOPE_ATTR_FFT_CENTER_FREQUENCY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 241
#define RSSCOPE_ATTR_FFT_FREQUENCY_SPAN                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 242
#define RSSCOPE_ATTR_FFT_FULL_SPAN                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 243
#define RSSCOPE_ATTR_FFT_START_FREQUENCY                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 244
#define RSSCOPE_ATTR_FFT_STOP_FREQUENCY                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 245
#define RSSCOPE_ATTR_FFT_WINDOW_TYPE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 246
#define RSSCOPE_ATTR_FFT_REFERENCE_LEVEL                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 247
#define RSSCOPE_ATTR_FFT_MAGNITUDE_RANGE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 248
#define RSSCOPE_ATTR_FFT_MAGNITUDE_UNIT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 249
#define RSSCOPE_ATTR_FFT_PHASE_UNIT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 250
#define RSSCOPE_ATTR_FFP_PHASE_UNWRAP_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 251
#define RSSCOPE_ATTR_FFT_NOISE_SUPPRESSION_ENABLED                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 252
#define RSSCOPE_ATTR_FFT_NOISE_SUPPRESSION_THRESHOLD                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 253
#define RSSCOPE_ATTR_FFT_RESOLUTION_BANDWIDTH                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 254
#define RSSCOPE_ATTR_FFT_RESOLUTION_BANDWIDTH_COUPLING_ENABLED              RS_SPECIFIC_PUBLIC_ATTR_BASE + 255
#define RSSCOPE_ATTR_FFT_RESOLUTION_BANDWIDTH_RATIO                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 256
#define RSSCOPE_ATTR_FFT_EFFECTIVE_RESOLUTION_BANDWIDTH                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 257
#define RSSCOPE_ATTR_FFT_RESOLUTION_BANDWIDTH_GATE_COUPLING                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 258
#define RSSCOPE_ATTR_FFT_FRAME_ARITHMETIC                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 259
#define RSSCOPE_ATTR_FFT_FRAME_MAX_FRAME_COUNT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 260
#define RSSCOPE_ATTR_FFT_FRAME_COVERAGE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 261
#define RSSCOPE_ATTR_FFT_FRAME_OVERLAP_FACTOR                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 262
#define RSSCOPE_ATTR_FFT_GATE_ENABLED                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 263
#define RSSCOPE_ATTR_FFT_GATE_MODE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 264
#define RSSCOPE_ATTR_FFT_GATE_START                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 265
#define RSSCOPE_ATTR_FFT_GATE_STOP                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 266
#define RSSCOPE_ATTR_FFT_GATE_DISPLAY_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 267
#define RSSCOPE_ATTR_FFT_GATE_ZOOM_COUPLING_ENABLED                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 268
#define RSSCOPE_ATTR_MATH_WAVEFORM_HEADER                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 337
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_HEADER                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 269
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_SOURCE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 270
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_DISPLAY_ENABLED                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 271
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_NAME                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 272
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_LOAD                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 273
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_SAVE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 274
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_DELETE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 275
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_UPDATE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 276
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_CLEAR                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 277
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_RESTORE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 278
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_VERTICAL_COUPLING                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 280
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_VERTICAL_SCALE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 281
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_VERTICAL_POSITION                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 282
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_VERTICAL_STRETCHING_ENABLED         RS_SPECIFIC_PUBLIC_ATTR_BASE + 283
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_VERTICAL_OFFSET                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 284
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_VERTICAL_FACTOR                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 285
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_HORZ_COUPLING                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 286
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_HORZ_STRETCHING_ENABLED             RS_SPECIFIC_PUBLIC_ATTR_BASE + 287
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_HORZ_OFFSET                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 288
#define RSSCOPE_ATTR_REFERENCE_WAVEFORM_HORZ_FACTOR                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 289
#define RSSCOPE_ATTR_MASK_CREATE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 290
#define RSSCOPE_ATTR_MASK_DELETE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 291
#define RSSCOPE_ATTR_MASK_RESULTS_CLEAR                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 292
#define RSSCOPE_ATTR_MASK_SEGMENT_ADD                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 294
#define RSSCOPE_ATTR_MASK_COPY_WAVEFORM                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 657
#define RSSCOPE_ATTR_NEW_SEARCH                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 338
#define RSSCOPE_ATTR_DELETE_SEARCH                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 339
#define RSSCOPE_ATTR_SEARCH_NEXT_RESULT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 340
#define RSSCOPE_ATTR_SEARCH_ALL_RESULTS                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 341
#define RSSCOPE_ATTR_CLEAR_SEARCH_RESULTS                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 342
#define RSSCOPE_ATTR_SEARCH_TRIGGER_LEVEL_AUTO_FIND                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 343
#define RSSCOPE_ATTR_SEARCH_COPY_FROM_A                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 344
#define RSSCOPE_ATTR_SEARCH_COPY_FROM_B                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 345
#define RSSCOPE_ATTR_PROTOCOL_STATE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 346
#define RSSCOPE_ATTR_PROTOCOL_TYPE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 347
#define RSSCOPE_ATTR_PROTOCOL_LABEL                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 348
#define RSSCOPE_ATTR_PROTOCOL_DISPLAY_RESULT_TABLE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 349
#define RSSCOPE_ATTR_PROTOCOL_TRANSLATION_STATE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 658
#define RSSCOPE_ATTR_PROTOCOL_LABEL_LIST                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 672
#define RSSCOPE_ATTR_PROTOCOL_I2C_SOURCE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 350
#define RSSCOPE_ATTR_PROTOCOL_I2C_THRESHOLD                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 351
#define RSSCOPE_ATTR_PROTOCOL_I2C_TECHNOLOGY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 352
#define RSSCOPE_ATTR_PROTOCOL_I2C_RW_BIT                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 659
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_MODE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 353
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_NO_ACK                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 354
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ACCESS_BIT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 357
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_TYPE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 358
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_CONDITION                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 551
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_MIN                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 359
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_MAX                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 361
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_OR_STATE                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 552
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_OR_TYPE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 553
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_OR_ACCESS_BIT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 554
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_OR                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 555
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_POSITION_CONDITION                RS_SPECIFIC_PUBLIC_ATTR_BASE + 583
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_POSITION_MIN_MAX                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 584
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_DATA_CONDITION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 556
#define RSSCOPE_ATTR_PROTOCOL_I2C_TRIGGER_PATTERN_MIN_MAX                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 585
#define RSSCOPE_ATTR_PROTOCOL_I2C_FRAME_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 374
#define RSSCOPE_ATTR_PROTOCOL_I2C_FRAME_TRANSLATION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 660
#define RSSCOPE_ATTR_PROTOCOL_SPI_BIT_ORDER                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 380
#define RSSCOPE_ATTR_PROTOCOL_SPI_WORD_LENGTH                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 381
#define RSSCOPE_ATTR_PROTOCOL_SPI_SOURCE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 382
#define RSSCOPE_ATTR_PROTOCOL_SPI_POLARITY                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 383
#define RSSCOPE_ATTR_PROTOCOL_SPI_THRESHOLD                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 384
#define RSSCOPE_ATTR_PROTOCOL_SPI_TECHNOLOGY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 385
#define RSSCOPE_ATTR_PROTOCOL_SPI_FRAME_START_CONDITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 484
#define RSSCOPE_ATTR_PROTOCOL_SPI_FRAME_START_TIMEOUT                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 485
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_MODE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 386
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_POSITION_CONDITION                RS_SPECIFIC_PUBLIC_ATTR_BASE + 586
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_DATA_ALIGNMENT                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 387
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_DATA_INDEX_MIN                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 388
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_DATA_INDEX_MAX                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 587
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_CONDITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 389
#define RSSCOPE_ATTR_PROTOCOL_SPI_TRIGGER_PATTERN                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 557
#define RSSCOPE_ATTR_PROTOCOL_SPI_FRAME_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 393
#define RSSCOPE_ATTR_PROTOCOL_UART_SOURCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 401
#define RSSCOPE_ATTR_PROTOCOL_UART_THRESHOLD                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 402
#define RSSCOPE_ATTR_PROTOCOL_UART_TECHNOLOGY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 403
#define RSSCOPE_ATTR_PROTOCOL_UART_BIT_RATE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 404
#define RSSCOPE_ATTR_PROTOCOL_UART_PARITY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 405
#define RSSCOPE_ATTR_PROTOCOL_UART_INTERFRAME_TIME                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 406
#define RSSCOPE_ATTR_PROTOCOL_UART_POLARITY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 407
#define RSSCOPE_ATTR_PROTOCOL_UART_STOP_BITS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 408
#define RSSCOPE_ATTR_PROTOCOL_UART_DATA_BITS_COUNT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 409
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_MODE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 410
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_SOURCE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 411
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_DATA_PATTERN                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 412
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_DATA_PATTERN_CONDITION           RS_SPECIFIC_PUBLIC_ATTR_BASE + 413
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_DATA_POSITION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 414
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_DATA_POSITION_INDEX_MIN          RS_SPECIFIC_PUBLIC_ATTR_BASE + 415
#define RSSCOPE_ATTR_PROTOCOL_UART_TRIGGER_DATA_POSITION_INDEX_MAX          RS_SPECIFIC_PUBLIC_ATTR_BASE + 416
#define RSSCOPE_ATTR_PROTOCOL_UART_WORD_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 418
#define RSSCOPE_ATTR_PROTOCOL_LIN_SOURCE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 486
#define RSSCOPE_ATTR_PROTOCOL_LIN_THRESHOLD                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 487
#define RSSCOPE_ATTR_PROTOCOL_LIN_TECHNOLOGY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 488
#define RSSCOPE_ATTR_PROTOCOL_LIN_STANDARD                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 489
#define RSSCOPE_ATTR_PROTOCOL_LIN_BIT_RATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 490
#define RSSCOPE_ATTR_PROTOCOL_LIN_POLARITY                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 491
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_MODE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 492
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_CONDITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 493
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_PATTERN_MIN                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 494
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_PATTERN_MAX                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 495
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_ADDRESS_OR_STATE                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 558
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_ADDRESS_OR                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 559
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_DATA_CONDITION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 588
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_DATA_LENGTH                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 589
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_DATA_TRANSFER                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 590
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_ERROR                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 496
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_CRC_ERROR_PATTERN                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 560
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_CRC_ERROR_DATA_LENGTH             RS_SPECIFIC_PUBLIC_ATTR_BASE + 561
#define RSSCOPE_ATTR_PROTOCOL_LIN_TRIGGER_CRC_STANDARD                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 661
#define RSSCOPE_ATTR_PROTOCOL_LIN_FRAME_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 497
#define RSSCOPE_ATTR_PROTOCOL_LIN_FRAME_TRANSLATION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 662
#define RSSCOPE_ATTR_PROTOCOL_CAN_SOURCE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 507
#define RSSCOPE_ATTR_PROTOCOL_CAN_LINE_TYPE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 508
#define RSSCOPE_ATTR_PROTOCOL_CAN_THRESHOLD                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 509
#define RSSCOPE_ATTR_PROTOCOL_CAN_TECHNOLOGY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 510
#define RSSCOPE_ATTR_PROTOCOL_CAN_BIT_RATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 511
#define RSSCOPE_ATTR_PROTOCOL_CAN_JUMP_WIDTH                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 512
#define RSSCOPE_ATTR_PROTOCOL_CAN_SAMPLE_POINT_ABS                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 513
#define RSSCOPE_ATTR_PROTOCOL_CAN_SAMPLE_POINT_REL                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 514
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_MODE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 515
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_FRAME_TYPE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 516
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_ID_TYPE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 517
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_CONDITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 518
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_PATTERN_MIN                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 519
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_PATTERN_MAX                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 520
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_FRAME_ENDIANNESS                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 521
#define RSSCOPE_ATTR_PROTOCOL_CAN_TRIGGER_ERROR                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 522
#define RSSCOPE_ATTR_PROTOCOL_CAN_FRAME_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 523
#define RSSCOPE_ATTR_PROTOCOL_CAN_FRAME_TRANSLATION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 663
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 591
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_SOURCE_TYPE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 592
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_SINGLE_POLARITY                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 593
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_SINGLE_PRESET_TRESHOLD                RS_SPECIFIC_PUBLIC_ATTR_BASE + 594
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_DIFF_PRESET_TRESHOLD                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 595
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRESHOLD                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 596
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_LOGIC_PRESET_TRESHOLD                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 597
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_LOGIC_TRESHOLD                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 598
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_BIT_RATE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 599
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_CHANNEL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 600
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_SEPARATE_HEADER_BITS                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 601
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_TYPE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 602
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_INDICATOR_BITS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 603
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_CONDITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 604
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_PATTERN_MIN                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 605
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_PATTERN_MAX                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 606
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_PAYLOAD_MIN_MAX               RS_SPECIFIC_PUBLIC_ATTR_BASE + 607
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_CYCLE_MIN_MAX                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 608
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_CYCLE_STEP                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 609
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_POSITION_MIN_MAX              RS_SPECIFIC_PUBLIC_ATTR_BASE + 610
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_SYMBOL                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 611
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_TRIGGER_ERROR                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 612
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_COUNT                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 613
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_CYCLE_COUNT                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 614
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_STATUS                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 615
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_START_STOP                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 616
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_TYPE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 617
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_FIELD_VALUE                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 618
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_FIELD_STATUS                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 619
#define RSSCOPE_ATTR_PROTOCOL_FLEXRAY_FRAME_TRANSLATION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 664
#define RSSCOPE_ATTR_MSO_BUS_STATE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 620
#define RSSCOPE_ATTR_MSO_DISPLAY_SHOW_SETTINGS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 621
#define RSSCOPE_ATTR_MSO_DISPLAY_REPRESENTATION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 622
#define RSSCOPE_ATTR_MSO_CLOCKED_BUS_STATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 673
#define RSSCOPE_ATTR_MSO_CLOCKED_BUS                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 623
#define RSSCOPE_ATTR_MSO_CLOCKED_BUS_SLOPE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 674
#define RSSCOPE_ATTR_MSO_SIGNAL_ASSIGN_STATE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 624
#define RSSCOPE_ATTR_MSO_SIGNAL_LABEL                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 625
#define RSSCOPE_ATTR_MSO_SIGNAL_DESKEW                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 626
#define RSSCOPE_ATTR_MSO_SIGNAL_DESKEW_ALL_CHANNELS                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 696
#define RSSCOPE_ATTR_MSO_TECHNOLOGY                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 697
#define RSSCOPE_ATTR_MSO_TRESHOLD                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 627
#define RSSCOPE_ATTR_MSO_HYSTERESIS                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 628
#define RSSCOPE_ATTR_MSO_CHANNEL_COUPLING                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 629
#define RSSCOPE_ATTR_MSO_TECHNOLOGY_ALL_CHANNELS                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 675
#define RSSCOPE_ATTR_MSO_TRESHOLD_ALL_CHANNELS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 676
#define RSSCOPE_ATTR_MSO_HYSTERESIS_ALL_CHANNELS                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 677
#define RSSCOPE_ATTR_MSO_REMOVE_ALL_ASSIGNED_CHANNELS                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 630
#define RSSCOPE_ATTR_MSO_TRIGGER_TYPE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 631
#define RSSCOPE_ATTR_MSO_TRIGGER_SOURCE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 632
#define RSSCOPE_ATTR_MSO_TRIGGER_EXPRESSION                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 633
#define RSSCOPE_ATTR_MSO_TRIGGER_CLOCK_SOURCE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 634
#define RSSCOPE_ATTR_MSO_TRIGGER_POLARITY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 635
#define RSSCOPE_ATTR_MSO_EDGE_TRIGGER_SLOPE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 636
#define RSSCOPE_ATTR_MSO_WIDTH_TRIGGER_POLARITY                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 637
#define RSSCOPE_ATTR_MSO_WIDTH_TRIGGER_CONDITION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 638
#define RSSCOPE_ATTR_MSO_WIDTH_TRIGGER_WIDTH                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 639
#define RSSCOPE_ATTR_MSO_WIDTH_TRIGGER_DELTA                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 640
#define RSSCOPE_ATTR_MSO_TIMEOUT_TRIGGER_VALUE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 641
#define RSSCOPE_ATTR_MSO_TIMEOUT_TRIGGER_CONDITION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 642
#define RSSCOPE_ATTR_MSO_DATA2CLOCK_TRIGGER_HOLD_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 643
#define RSSCOPE_ATTR_MSO_DATA2CLOCK_TRIGGER_SETUP_TIME                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 644
#define RSSCOPE_ATTR_MSO_TRIGGER_CHANNEL_STATUS_BIT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 645
#define RSSCOPE_ATTR_MSO_PATTERN_TRIGGER_MODE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 646
#define RSSCOPE_ATTR_MSO_PATTERN_TRIGGER_TIMEOUT_MODE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 647
#define RSSCOPE_ATTR_MSO_PATTERN_TRIGGER_TIMEOUT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 648
#define RSSCOPE_ATTR_MSO_PATTERN_TRIGGER_WIDTH                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 649
#define RSSCOPE_ATTR_MSO_PATTERN_TRIGGER_DELTA                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 650
#define RSSCOPE_ATTR_MSO_PATTERN_TRIGGER_CONDITION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 651
#define RSSCOPE_ATTR_MSO_SERIAL_PATTERN_TRIGGER_PATTERN                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 652
#define RSSCOPE_ATTR_IQ_MODE_STATE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 678
#define RSSCOPE_ATTR_IQ_RELATIVE_BANDWIDTH                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 679
#define RSSCOPE_ATTR_IQ_SAMPLE_RATE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 680
#define RSSCOPE_ATTR_IQ_RECORD_LENGTH                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 681
#define RSSCOPE_ATTR_IQ_FILTER_BANDWIDTH                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 682
#define RSSCOPE_ATTR_IQ_INPUT_TYPE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 683
#define RSSCOPE_ATTR_IQ_INPUT_MODE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 684
#define RSSCOPE_ATTR_IQ_CARRIER_FREQUENCY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 685
#define RSSCOPE_ATTR_IQ_REAL_SIDEBAND                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 686
#define RSSCOPE_ATTR_IQ_COMPLEX_SIDEBAND                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 687
#define RSSCOPE_ATTR_PERSISTENCE_STATE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 422
#define RSSCOPE_ATTR_INFINITE_PERSISTENCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 423
#define RSSCOPE_ATTR_PERSISTENCE_TIME                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 424
#define RSSCOPE_ATTR_PERSISTENCE_RESET                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 425
#define RSSCOPE_ATTR_SIGNAL_STYLE_INTENSITY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 426
#define RSSCOPE_ATTR_SIGNAL_STYLE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 427
#define RSSCOPE_ATTR_USE_COLOR_TABLE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 428
#define RSSCOPE_ATTR_ASSIGN_COLOR_TABLE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 429
#define RSSCOPE_ATTR_ADD_COLOR_TABLE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 430
#define RSSCOPE_ATTR_REMOVE_COLOR_TABLE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 431
#define RSSCOPE_ATTR_COLOR_TABLE_COUNT                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 432
#define RSSCOPE_ATTR_COLOR_TABLE_APPEND_NEW_ROW                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 433
#define RSSCOPE_ATTR_DIAGRAM_SHOW_GRID                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 434
#define RSSCOPE_ATTR_DIAGRAM_SHOW_CROSSHAIR                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 435
#define RSSCOPE_ATTR_DIAGRAM_SHOW_LABELS                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 436
#define RSSCOPE_ATTR_DIAGRAM_SHOW_TAB_TITLES                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 437
#define RSSCOPE_ATTR_DIAGRAM_KEEP_Y_GRID_FIXED                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 438
#define RSSCOPE_ATTR_SIGNAL_BAR_STATE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 439
#define RSSCOPE_ATTR_SIGNAL_BAR_POSITION                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 440
#define RSSCOPE_ATTR_SIGNAL_BAR_AUTO_HIDE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 441
#define RSSCOPE_ATTR_SIGNAL_BAR_HIDE_TIME                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 442
#define RSSCOPE_ATTR_SIGNAL_BAR_HIDE_HEAD                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 443
#define RSSCOPE_ATTR_SIGNAL_BAR_HIDING_TRANSPARENCY                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 444
#define RSSCOPE_ATTR_SIGNAL_BAR_BORDER_COLOR                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 445
#define RSSCOPE_ATTR_SIGNAL_BAR_FILL_COLOR                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 446
#define RSSCOPE_ATTR_RESULT_BOX_POSITION                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 698
#define RSSCOPE_ATTR_REMOVE_DIAGRAM                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 447
#define RSSCOPE_ATTR_DISPLAY_DIAGRAM                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 448
#define RSSCOPE_ATTR_REMOVE_WAVEFORM_FROM_DIAGRAM                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 449
#define RSSCOPE_ATTR_XY_DIAGRAM_STATE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 450
#define RSSCOPE_ATTR_XY_DIAGRAM_RATIO                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 451
#define RSSCOPE_ATTR_SWAP_XY_DIAGRAM                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 452
#define RSSCOPE_ATTR_XY_DIAGRAM_SOURCE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 453
#define RSSCOPE_ATTR_HISTORY_STATE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 534
#define RSSCOPE_ATTR_HISTORY_START_INDEX                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 535
#define RSSCOPE_ATTR_HISTORY_STOP_INDEX                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 536
#define RSSCOPE_ATTR_HISTORY_ACQUISITION_VIEW                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 537
#define RSSCOPE_ATTR_HISTORY_ACQUISITION_TIME                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 538
#define RSSCOPE_ATTR_HISTORY_AUTO_REPEAT                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 539
#define RSSCOPE_ATTR_HISTORY_PLAYBACK                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 540
#define RSSCOPE_ATTR_HISTORY_TIME_STAMP                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 541
#define RSSCOPE_ATTR_HISTORY_DATE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 542
#define RSSCOPE_ATTR_HISTORY_GET_ACQUISITIONS_COUNT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 562
#define RSSCOPE_ATTR_SAVE                                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 295
#define RSSCOPE_ATTR_RECALL                                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 296
#define RSSCOPE_ATTR_DRIVES                                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 297
#define RSSCOPE_ATTR_CHANGE_DRIVE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 298
#define RSSCOPE_ATTR_CURRENT_DIRECTORY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 299
#define RSSCOPE_ATTR_CREATE_DIRECTORY                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 300
#define RSSCOPE_ATTR_REMOVE_DIRECTORY                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 301
#define RSSCOPE_ATTR_DELETE_FILE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 302
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 563
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_SCOPE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 564
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_SCOPE_CURSOR                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 565
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_SCOPE_GATE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 566
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_SCOPE_START                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 567
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_SCOPE_STOP                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 568
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_DATA_LOGGING                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 569
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_FILE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 570
#define RSSCOPE_ATTR_WAVEFORM_EXPORT                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 571
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_INTERLEAVED_XY                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 699
#define RSSCOPE_ATTR_WAVEFORM_EXPORT_RAW_VALUES                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 700
#define RSSCOPE_ATTR_HARDCOPY_FILE_NAME                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 303
#define RSSCOPE_ATTR_HARDCOPY_COLOR                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 454
#define RSSCOPE_ATTR_HARDCOPY_DEVICE_DESTINATION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 455
#define RSSCOPE_ATTR_HARDCOPY_DEVICE_LANGUAGE_OUTPUT_FORMAT                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 456
#define RSSCOPE_ATTR_HARDCOPY_DEVICE_ORIENTATION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 457
#define RSSCOPE_ATTR_HARDCOPY_PRINT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 458
#define RSSCOPE_ATTR_HARDCOPY_SELECT_PRINTER                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 459
#define RSSCOPE_ATTR_HARDCOPY_GET_FIRST_PRINTER                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 460
#define RSSCOPE_ATTR_HARDCOPY_GET_NEXT_PRINTER                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 461
#define RSSCOPE_ATTR_FIRMWARE_SHUTDOWN                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 462
#define RSSCOPE_ATTR_FIRMWARE_VERSION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 463
#define RSSCOPE_ATTR_COMPUTER_NAME                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 464
#define RSSCOPE_ATTR_MATERIAL_NUMBER                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 465
#define RSSCOPE_ATTR_SERIAL_NUMBER                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 466
#define RSSCOPE_ATTR_START_SELFTEST                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 467
#define RSSCOPE_ATTR_SELFTEST_STATUS                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 468
#define RSSCOPE_ATTR_SET_QUERY_PATTERN_FORMAT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 572
#define RSSCOPE_ATTR_ID_QUERY_RESPONSE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 304
#define RSSCOPE_ATTR_CALIBRATION                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 305
#define RSSCOPE_ATTR_SELF_TEST_QUERY                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 306
#define RSSCOPE_ATTR_SYSTEM_ERROR                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 307
#define RSSCOPE_ATTR_QUESTIONABLE_REGISTER                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 308

// rsscope_rngSampleMode
#define RSSCOPE_VAL_REAL_TIME                                               0
#define RSSCOPE_VAL_EQUIVALENT_TIME                                         1
#define RSSCOPE_VAL_INTERPOLATED_TIME                                       2

// rsscope_rngWaveformArithmetics
#define RSSCOPE_VAL_OFF                                                     0
#define RSSCOPE_VAL_ENVELOPE                                                1
#define RSSCOPE_VAL_AVERAGE                                                 2
#define RSSCOPE_VAL_SMOOTH                                                  3

// rsscope_rngVerticalCoupling
#define RSSCOPE_VAL_AC                                                      0
#define RSSCOPE_VAL_DC                                                      1
#define RSSCOPE_VAL_DC_LIMIT                                                2

// rsscope_rngChannelBWLimit
#define RSSCOPE_VAL_BW_FULL                                                 0
#define RSSCOPE_VAL_BW_800                                                  1
#define RSSCOPE_VAL_BW_200                                                  2
#define RSSCOPE_VAL_BW_20                                                   3

// rsscope_rngTriggerMode
#define RSSCOPE_VAL_NORMAL                                                  0
#define RSSCOPE_VAL_AUTO                                                    1
#define RSSCOPE_VAL_FREERUN                                                 2

// rsscope_rngTriggerSource
#define RSSCOPE_VAL_CHANNEL1                                                1
#define RSSCOPE_VAL_CHANNEL2                                                2
#define RSSCOPE_VAL_CHANNEL3                                                3
#define RSSCOPE_VAL_CHANNEL4                                                4
#define RSSCOPE_VAL_EXTERNAL                                                5
#define RSSCOPE_VAL_SBUS                                                    6
#define RSSCOPE_VAL_D0                                                      7
#define RSSCOPE_VAL_D1                                                      8
#define RSSCOPE_VAL_D2                                                      9
#define RSSCOPE_VAL_D3                                                      10
#define RSSCOPE_VAL_D4                                                      11
#define RSSCOPE_VAL_D5                                                      12
#define RSSCOPE_VAL_D6                                                      13
#define RSSCOPE_VAL_D7                                                      14
#define RSSCOPE_VAL_D8                                                      15
#define RSSCOPE_VAL_D9                                                      16
#define RSSCOPE_VAL_D10                                                     17
#define RSSCOPE_VAL_D11                                                     18
#define RSSCOPE_VAL_D12                                                     19
#define RSSCOPE_VAL_D13                                                     20
#define RSSCOPE_VAL_D14                                                     21
#define RSSCOPE_VAL_D15                                                     22
#define RSSCOPE_VAL_DALL                                                    23
#define RSSCOPE_VAL_MSOB1                                                   24
#define RSSCOPE_VAL_MSOB2                                                   25
#define RSSCOPE_VAL_MSOB3                                                   26
#define RSSCOPE_VAL_MSOB4                                                   27

// rsscope_rngTriggerType
#define RSSCOPE_VAL_EDGE_TRIGGER                                            0
#define RSSCOPE_VAL_WIDTH_TRIGGER                                           1
#define RSSCOPE_VAL_RUNT_TRIGGER                                            2
#define RSSCOPE_VAL_GLITCH_TRIGGER                                          3
#define RSSCOPE_VAL_WINDOW_TRIGGER                                          4
#define RSSCOPE_VAL_TIMEOUT_TRIGGER                                         5
#define RSSCOPE_VAL_INTERVAL_TRIGGER                                        6
#define RSSCOPE_VAL_SLEW_RATE_TRIGGER                                       7
#define RSSCOPE_VAL_DATA_TO_CLOCK_TRIGGER                                   8
#define RSSCOPE_VAL_PATTERN_TRIGGER                                         9
#define RSSCOPE_VAL_SERIAL_PATTERN_TRIGGER                                  11
#define RSSCOPE_VAL_STATE_TRIGGER                                           12
#define RSSCOPE_VAL_NFC_TRIGGER                                             13
#define RSSCOPE_VAL_TV_TRIGGER                                              14

// rsscope_rngTriggerSlope
#define RSSCOPE_VAL_POSITIVE                                                0
#define RSSCOPE_VAL_NEGATIVE                                                1
#define RSSCOPE_VAL_EITHER                                                  2

// rsscope_rngTriggerCoupling
#define RSSCOPE_VAL_DCL                                                     2

// rsscope_rngWidthCondition
#define RSSCOPE_VAL_SHORTER                                                 0
#define RSSCOPE_VAL_LONGER                                                  1
#define RSSCOPE_VAL_WITHIN                                                  2
#define RSSCOPE_VAL_OUTSIDE                                                 3

// rsscope_rngTVTriggerEvent
#define RSSCOPE_VAL_TV_EVENT_EVEN                                           0
#define RSSCOPE_VAL_TV_EVENT_ODD                                            1
#define RSSCOPE_VAL_TV_EVENT_ANY_FIELD                                      2
#define RSSCOPE_VAL_TV_EVENT_LINE                                           3
#define RSSCOPE_VAL_TV_EVENT_ANY_LINE                                       4

// rsscope_rngChannelPatternCombination
#define RSSCOPE_VAL_AND                                                     0
#define RSSCOPE_VAL_OR                                                      1

// rsscope_rngFalseTrue
#define RSSCOPE_VAL_FALSE                                                   0
#define RSSCOPE_VAL_TRUE                                                    1

// rsscope_rngBTriggerDelayType
#define RSSCOPE_VAL_DELAY                                                   0
#define RSSCOPE_VAL_EVENTS                                                  1

// rsscope_rngCursorFunction
#define RSSCOPE_VAL_CURSOR_HORIZONTAL                                       0
#define RSSCOPE_VAL_CURSOR_VERTICAL                                         1
#define RSSCOPE_VAL_CURSOR_PAIRED                                           2
#define RSSCOPE_VAL_CURSOR_HRAT                                             3
#define RSSCOPE_VAL_CURSOR_VRAT                                             4
#define RSSCOPE_VAL_CURSOR_PPC                                              5
#define RSSCOPE_VAL_CURSOR_NPC                                              6
#define RSSCOPE_VAL_CURSOR_REC                                              7
#define RSSCOPE_VAL_CURSOR_FEC                                              8
#define RSSCOPE_VAL_CURSOR_MEAN                                             9
#define RSSCOPE_VAL_CURSOR_RMS                                              10
#define RSSCOPE_VAL_CURSOR_RTIM                                             11
#define RSSCOPE_VAL_CURSOR_FTIM                                             12
#define RSSCOPE_VAL_CURSOR_PEAK                                             13
#define RSSCOPE_VAL_CURSOR_UPE                                              14
#define RSSCOPE_VAL_CURSOR_LPE                                              15

// rsscope_rngWaveformParameter
#define RSSCOPE_VAL_WAV_NONE                                                0
#define RSSCOPE_VAL_WAV_C1W1                                                1
#define RSSCOPE_VAL_WAV_C1W2                                                2
#define RSSCOPE_VAL_WAV_C1W3                                                3
#define RSSCOPE_VAL_WAV_C2W1                                                4
#define RSSCOPE_VAL_WAV_C2W2                                                5
#define RSSCOPE_VAL_WAV_C2W3                                                6
#define RSSCOPE_VAL_WAV_C3W1                                                7
#define RSSCOPE_VAL_WAV_C3W2                                                8
#define RSSCOPE_VAL_WAV_C3W3                                                9
#define RSSCOPE_VAL_WAV_C4W1                                                10
#define RSSCOPE_VAL_WAV_C4W2                                                11
#define RSSCOPE_VAL_WAV_C4W3                                                12
#define RSSCOPE_VAL_WAV_M1                                                  13
#define RSSCOPE_VAL_WAV_M2                                                  14
#define RSSCOPE_VAL_WAV_M3                                                  15
#define RSSCOPE_VAL_WAV_M4                                                  16
#define RSSCOPE_VAL_WAV_M5                                                  17
#define RSSCOPE_VAL_WAV_R1                                                  18
#define RSSCOPE_VAL_WAV_R2                                                  19
#define RSSCOPE_VAL_WAV_R3                                                  20
#define RSSCOPE_VAL_WAV_R4                                                  21
#define RSSCOPE_VAL_WAV_XY1                                                 22
#define RSSCOPE_VAL_WAV_XY2                                                 23
#define RSSCOPE_VAL_WAV_XY3                                                 24
#define RSSCOPE_VAL_WAV_XY4                                                 25
#define RSSCOPE_VAL_WAV_MRES1                                               26
#define RSSCOPE_VAL_WAV_MRES2                                               27
#define RSSCOPE_VAL_WAV_MRES3                                               28
#define RSSCOPE_VAL_WAV_MRES4                                               29
#define RSSCOPE_VAL_WAV_MRES5                                               30
#define RSSCOPE_VAL_WAV_MRES6                                               31
#define RSSCOPE_VAL_WAV_MRES7                                               32
#define RSSCOPE_VAL_WAV_MRES8                                               33
#define RSSCOPE_VAL_WAV_SBUS1                                               34
#define RSSCOPE_VAL_WAV_SBUS2                                               35
#define RSSCOPE_VAL_WAV_SBUS3                                               36
#define RSSCOPE_VAL_WAV_SBUS4                                               37
#define RSSCOPE_VAL_WAV_D0                                                  38
#define RSSCOPE_VAL_WAV_D1                                                  39
#define RSSCOPE_VAL_WAV_D2                                                  40
#define RSSCOPE_VAL_WAV_D3                                                  41
#define RSSCOPE_VAL_WAV_D4                                                  42
#define RSSCOPE_VAL_WAV_D5                                                  43
#define RSSCOPE_VAL_WAV_D6                                                  44
#define RSSCOPE_VAL_WAV_D7                                                  45
#define RSSCOPE_VAL_WAV_D8                                                  46
#define RSSCOPE_VAL_WAV_D9                                                  47
#define RSSCOPE_VAL_WAV_D10                                                 48
#define RSSCOPE_VAL_WAV_D11                                                 49
#define RSSCOPE_VAL_WAV_D12                                                 50
#define RSSCOPE_VAL_WAV_D13                                                 51
#define RSSCOPE_VAL_WAV_D14                                                 52
#define RSSCOPE_VAL_WAV_D15                                                 53
#define RSSCOPE_VAL_WAV_MSOB1                                               54
#define RSSCOPE_VAL_WAV_MSOB2                                               55
#define RSSCOPE_VAL_WAV_MSOB3                                               56
#define RSSCOPE_VAL_WAV_MSOB4                                               57

// rsscope_rngMinMax
#define RSSCOPE_VAL_MIN                                                     0
#define RSSCOPE_VAL_MAX                                                     1
#define RSSCOPE_VAL_BOTH                                                    2

// rsscope_rngXRatioMeasurementUnit
#define RSSCOPE_VAL_UNIT_RATIO                                              0
#define RSSCOPE_VAL_UNIT_PCT                                                1
#define RSSCOPE_VAL_UNIT_DEGREE                                             2
#define RSSCOPE_VAL_UNIT_RAD                                                3

// rsscope_rngAcquisitionType
#define RSSCOPE_VAL_SAMPLE                                                  0
#define RSSCOPE_VAL_PEAK_DETECT                                             1
#define RSSCOPE_VAL_HI_RES                                                  2
#define RSSCOPE_VAL_RMS                                                     3

// rsscope_rngHorzRecordSelection
#define RSSCOPE_VAL_RESOLUTION                                              0
#define RSSCOPE_VAL_RECORD_TIME                                             1

// rsscope_rngInterpolation
#define RSSCOPE_VAL_SINE_X                                                  0
#define RSSCOPE_VAL_LINEAR                                                  1
#define RSSCOPE_VAL_SAMPLE_HOLD                                             2

// rsscope_rngCutOffFrequency
#define RSSCOPE_VAL_CUTOFF_KHZ5                                             0
#define RSSCOPE_VAL_CUTOFF_KHZ50                                            1
#define RSSCOPE_VAL_CUTOFF_MHZ50                                            2

// rsscope_rngFilterType
#define RSSCOPE_VAL_FILTER_OFF                                              0
#define RSSCOPE_VAL_FILTER_LOW_PASS                                         1
#define RSSCOPE_VAL_FILTER_HIGH_PASS                                        2

// rsscope_rngRuntCondition
#define RSSCOPE_VAL_ANY                                                     4

// rsscope_rngWindowCondition
#define RSSCOPE_VAL_ENTER                                                   0
#define RSSCOPE_VAL_EXIT                                                    1

// rsscope_rngTimeoutCondition
#define RSSCOPE_VAL_TIMEOUT_LOW                                             0
#define RSSCOPE_VAL_TIMEOUT_HIGH                                            1
#define RSSCOPE_VAL_TIMEOUT_EITHER                                          2

// rsscope_rngPatternMode
#define RSSCOPE_VAL_PATTERN_OFF                                             0
#define RSSCOPE_VAL_PATTERN_TIMEOUT                                         1
#define RSSCOPE_VAL_PATTERN_WIDTH                                           2

// rsscope_rngPatternTimeoutMode
#define RSSCOPE_VAL_PATTERN_TIMEOUT_LOW                                     0
#define RSSCOPE_VAL_PATTERN_TIMEOUT_HIGH                                    1

// rsscope_rngTriggerQualificationLogic
#define RSSCOPE_VAL_LOGIC_DIRECT                                            0
#define RSSCOPE_VAL_LOGIC_NEGATE                                            1

// rsscope_rngLogic
#define RSSCOPE_VAL_NAND                                                    2
#define RSSCOPE_VAL_NOR                                                     3

// rsscope_rngAutoManual
#define RSSCOPE_VAL_MANUAL                                                  0

// rsscope_rngTriggerSequence
#define RSSCOPE_VAL_SEQ_AONLY                                               0
#define RSSCOPE_VAL_SEQ_ABR                                                 1

// rsscope_rngHoldoffMode
#define RSSCOPE_VAL_HOLDOFF_OFF                                             0
#define RSSCOPE_VAL_HOLDOFF_AUTO                                            1
#define RSSCOPE_VAL_HOLDOFF_TIME                                            2
#define RSSCOPE_VAL_HOLDOFF_EVENTS                                          3
#define RSSCOPE_VAL_HOLDOFF_RANDOM                                          4

// rsscope_rngMeasurementCategory
#define RSSCOPE_VAL_AMPTIME                                                 0
#define RSSCOPE_VAL_EYE                                                     1
#define RSSCOPE_VAL_SPECTRUM                                                2
#define RSSCOPE_VAL_HISTOGRAM                                               3

// rsscope_rngAmplitudeTimeMeasurementType
#define RSSCOPE_VAL_MEAS_HIGH                                               1
#define RSSCOPE_VAL_MEAS_LOW                                                2
#define RSSCOPE_VAL_MEAS_AMPLITUDE                                          3
#define RSSCOPE_VAL_MEAS_MAXIMUM                                            4
#define RSSCOPE_VAL_MEAS_MINIMUM                                            5
#define RSSCOPE_VAL_MEAS_PEAK_TO_PEAK                                       6
#define RSSCOPE_VAL_MEAS_MEAN                                               7
#define RSSCOPE_VAL_MEAS_RMS                                                8
#define RSSCOPE_VAL_MEAS_STD_DEVIATION                                      9
#define RSSCOPE_VAL_MEAS_POS_OVERSHOOT                                      10
#define RSSCOPE_VAL_MEAS_NEG_OVERSHOOT                                      11
#define RSSCOPE_VAL_MEAS_AREA                                               12
#define RSSCOPE_VAL_MEAS_RISE_TIME                                          13
#define RSSCOPE_VAL_MEAS_FALL_TIME                                          14
#define RSSCOPE_VAL_MEAS_POS_PULSE                                          15
#define RSSCOPE_VAL_MEAS_NEG_PULSE                                          16
#define RSSCOPE_VAL_MEAS_PERIOD                                             17
#define RSSCOPE_VAL_MEAS_FREQUENCY                                          18
#define RSSCOPE_VAL_MEAS_POS_DUTY_CYCLE                                     19
#define RSSCOPE_VAL_MEAS_NEG_DUTY_CYCLE                                     20
#define RSSCOPE_VAL_MEAS_CYCLE_AREA                                         21
#define RSSCOPE_VAL_MEAS_CYCLE_MEAN                                         22
#define RSSCOPE_VAL_MEAS_CYCLE_RMS                                          23
#define RSSCOPE_VAL_MEAS_CYCLE_STD_DEV                                      24
#define RSSCOPE_VAL_MEAS_PULSE_COUNT                                        25
#define RSSCOPE_VAL_MEAS_DELAY                                              26
#define RSSCOPE_VAL_MEAS_PHASE                                              27
#define RSSCOPE_VAL_MEAS_BURST_WIDTH                                        28
#define RSSCOPE_VAL_MEAS_POS_SWITCHING                                      29
#define RSSCOPE_VAL_MEAS_NEG_SWITCHING                                      30
#define RSSCOPE_VAL_MEAS_PROBEMETER                                         31
#define RSSCOPE_VAL_MEAS_PULSE_TRAIN                                        32
#define RSSCOPE_VAL_MEAS_EDGE_COUNT                                         33
#define RSSCOPE_VAL_MEAS_SHT                                                34
#define RSSCOPE_VAL_MEAS_SHR                                                35
#define RSSCOPE_VAL_MEAS_SETUP                                              36
#define RSSCOPE_VAL_MEAS_HOLD                                               37

// rsscope_rngEyeJitterMeasurementType
#define RSSCOPE_VAL_MEAS_EXTINCTION_RATIO_PCT                               2
#define RSSCOPE_VAL_MEAS_EXTINCTION_RATIO_DBM                               3
#define RSSCOPE_VAL_MEAS_EYE_HEIGHT                                         4
#define RSSCOPE_VAL_MEAS_EYE_WIDTH                                          5
#define RSSCOPE_VAL_MEAS_EYE_TOP                                            6
#define RSSCOPE_VAL_MEAS_EYE_BASE                                           7
#define RSSCOPE_VAL_MEAS_Q_FACTOR                                           10
#define RSSCOPE_VAL_MEAS_RMS_NOISE                                          14
#define RSSCOPE_VAL_MEAS_SNR                                                15
#define RSSCOPE_VAL_MEAS_DUTY_CYCLE_DISTORTION                              16
#define RSSCOPE_VAL_MEAS_EYE_RISE_TIME                                      17
#define RSSCOPE_VAL_MEAS_EYE_FALL_TIME                                      18
#define RSSCOPE_VAL_MEAS_EYE_BIT_RATE                                       19
#define RSSCOPE_VAL_MEAS_EYE_AMPLITUDE                                      20
#define RSSCOPE_VAL_MEAS_PEAK_TO_PEAK_JITTER                                28
#define RSSCOPE_VAL_MEAS_STD_DEVIATION_JITTER                               29
#define RSSCOPE_VAL_MEAS_RMS_JITTER                                         30

// rsscope_rngSpectrumMeasurementType
#define RSSCOPE_VAL_MEAS_CHANNEL_POWER                                      1
#define RSSCOPE_VAL_MEAS_OCCUPIED_BANDWIDTH                                 2
#define RSSCOPE_VAL_MEAS_N_DB_DOWN                                          3
#define RSSCOPE_VAL_MEAS_THD                                                4

// rsscope_rngHistogramMeasurementType
#define RSSCOPE_VAL_MEAS_WAVEFORM_COUNT                                     1
#define RSSCOPE_VAL_MEAS_WAVEFORM_SAMPLES                                   2
#define RSSCOPE_VAL_MEAS_HISTOGRAM_SAMPLES                                  3
#define RSSCOPE_VAL_MEAS_HISTOGRAM_PEAK                                     4
#define RSSCOPE_VAL_MEAS_PEAK                                               5
#define RSSCOPE_VAL_MEAS_UPPER_PEAK                                         6
#define RSSCOPE_VAL_MEAS_LOWER_PEAK                                         7
#define RSSCOPE_VAL_MEAS_HISTOGRAM_MAXIMUM                                  8
#define RSSCOPE_VAL_MEAS_HISTOGRAM_MINIMUM                                  9
#define RSSCOPE_VAL_MEAS_MEDIAN                                             10
#define RSSCOPE_VAL_MEAS_MAXIMUM_MINIMUM                                    11
#define RSSCOPE_VAL_MEAS_HISTOGRAM_MEAN                                     12
#define RSSCOPE_VAL_MEAS_HISTOGRAM_STD_DEVIATION                            13
#define RSSCOPE_VAL_MEAS_M1ST                                               14
#define RSSCOPE_VAL_MEAS_M2ST                                               15
#define RSSCOPE_VAL_MEAS_M3ST                                               16
#define RSSCOPE_VAL_MEAS_MKP                                                17
#define RSSCOPE_VAL_MEAS_MKN                                                18

// rsscope_rngLimitCheck
#define RSSCOPE_VAL_INSIDE_LIMIT                                            0
#define RSSCOPE_VAL_UPPER_LIMIT                                             1
#define RSSCOPE_VAL_LOWER_LIMIT                                             2
#define RSSCOPE_VAL_OUTSIDE_LIMIT                                           3

// rsscope_rngProbabilityType
#define RSSCOPE_VAL_PROBABILITY_PEAK                                        0
#define RSSCOPE_VAL_PROBABILITY_UPPK                                        1
#define RSSCOPE_VAL_PROBABILITY_LWPK                                        2
#define RSSCOPE_VAL_PROBABILITY_MAX                                         3
#define RSSCOPE_VAL_PROBABILITY_MIN                                         4
#define RSSCOPE_VAL_PROBABILITY_MEDIAN                                      5
#define RSSCOPE_VAL_PROBABILITY_MEAN                                        6

// rsscope_rngLimitType
#define RSSCOPE_VAL_LIMIT_OFF                                               0
#define RSSCOPE_VAL_LIMIT_ONLY                                              1
#define RSSCOPE_VAL_LIMIT_MARGIN                                            2

// rsscope_rngMeasurementEvent
#define RSSCOPE_VAL_EVENT_NO_ACTION                                         0
#define RSSCOPE_VAL_EVENT_SUCCESS                                           1
#define RSSCOPE_VAL_EVENT_VIOLATION                                         2

// rsscope_rngAbsRel
#define RSSCOPE_VAL_ABS                                                     0
#define RSSCOPE_VAL_REL                                                     1

// rsscope_rngLowUpp
#define RSSCOPE_VAL_LOW                                                     0
#define RSSCOPE_VAL_UPP                                                     1

// rsscope_rngStatisticsMode
#define RSSCOPE_VAL_STAT_MODE_NONE                                          0
#define RSSCOPE_VAL_STAT_MODE_TIME                                          1
#define RSSCOPE_VAL_STAT_MODE_WAVEFORMS                                     2

// rsscope_rngFFTWindowType
#define RSSCOPE_VAL_RECTANGULAR                                             0
#define RSSCOPE_VAL_HAMMING                                                 1
#define RSSCOPE_VAL_HANN                                                    2
#define RSSCOPE_VAL_BLACKMAN                                                3
#define RSSCOPE_VAL_GAUSSIAN                                                4
#define RSSCOPE_VAL_FLATTOP                                                 5
#define RSSCOPE_VAL_KAISER                                                  6

// rsscope_rngRBWGateCoupling
#define RSSCOPE_VAL_COUPLING_LENGTH                                         0
#define RSSCOPE_VAL_COUPLING_RBW                                            1

// rsscope_rngFFTMagnitudeUnit
#define RSSCOPE_VAL_SCALE_LINEAR                                            0
#define RSSCOPE_VAL_SCALE_DBM                                               1
#define RSSCOPE_VAL_SCALE_DB                                                2
#define RSSCOPE_VAL_SCALE_DBUV                                              3
#define RSSCOPE_VAL_SCALE_DBMV                                              4
#define RSSCOPE_VAL_SCALE_DBV                                               5

// rsscope_rngFFTPhaseUnit
#define RSSCOPE_VAL_SCALE_DEG                                               0
#define RSSCOPE_VAL_SCALE_RAD                                               1

// rsscope_rngRefLevelRelative
#define RSSCOPE_VAL_FIVE                                                    0
#define RSSCOPE_VAL_TEN                                                     1
#define RSSCOPE_VAL_TWENTY                                                  2
#define RSSCOPE_VAL_USER_LEVEL                                              3

// rsscope_rngUserLevel
#define RSSCOPE_VAL_HIGH_LOW                                                0
#define RSSCOPE_VAL_LEVEL                                                   1

// rsscope_rngRefLevelAutoMode
#define RSSCOPE_VAL_REF_AUTO                                                0
#define RSSCOPE_VAL_REF_PPR                                                 1
#define RSSCOPE_VAL_REF_MPR                                                 2
#define RSSCOPE_VAL_REF_ABS_PEAK                                            3

// rsscope_rngRefWfmCoupling
#define RSSCOPE_VAL_COUPLED                                                 0
#define RSSCOPE_VAL_INDEPENDENT                                             1

// rsscope_rngRefWfmHorzCoupling
#define RSSCOPE_VAL_ORIGINAL                                                1

// rsscope_rngProbeButtonAction
#define RSSCOPE_VAL_PROBE_BUTTON_NO_ACTION                                  0
#define RSSCOPE_VAL_PROBE_BUTTON_RUN_CONTINUOUS                             1
#define RSSCOPE_VAL_PROBE_BUTTON_RUN_SINGLE                                 2
#define RSSCOPE_VAL_PROBE_BUTTON_AUTOSET                                    3
#define RSSCOPE_VAL_PROBE_BUTTON_AUTO_ZERO                                  4
#define RSSCOPE_VAL_PROBE_BUTTON_SET_OFFSET_TO_MEAN                         5

// rsscope_rngProbeState
#define RSSCOPE_VAL_PROBE_STATE_NDET                                        0
#define RSSCOPE_VAL_PROBE_STATE_DET                                         1

// rsscope_rngProbeFirmwareUpdateStatus
#define RSSCOPE_VAL_PROBE_FIRMWARE_UPDATE_STATUS_UNKNOWN                    0
#define RSSCOPE_VAL_PROBE_FIRMWARE_UPDATE_STATUS_MEASURING                  1
#define RSSCOPE_VAL_PROBE_FIRMWARE_UPDATE_STATUS_UPDATE                     2
#define RSSCOPE_VAL_PROBE_FIRMWARE_UPDATE_STATUS_FAILED                     3

// rsscope_rngProbeSelftestStatus
#define RSSCOPE_VAL_PROBE_SELFTEST_STATUS_FAILED                            0
#define RSSCOPE_VAL_PROBE_SELFTEST_STATUS_PASSED                            1
#define RSSCOPE_VAL_PROBE_SELFTEST_STATUS_UNDEFINED                         2

// rsscope_rngProtocolWaveformSource
#define RSSCOPE_VAL_PROTOCOL_WAV_NONE                                       0
#define RSSCOPE_VAL_PROTOCOL_WAV_C1W1                                       1
#define RSSCOPE_VAL_PROTOCOL_WAV_C2W1                                       2
#define RSSCOPE_VAL_PROTOCOL_WAV_C3W1                                       3
#define RSSCOPE_VAL_PROTOCOL_WAV_C4W1                                       4
#define RSSCOPE_VAL_PROTOCOL_WAV_M1                                         5
#define RSSCOPE_VAL_PROTOCOL_WAV_M2                                         6
#define RSSCOPE_VAL_PROTOCOL_WAV_M3                                         7
#define RSSCOPE_VAL_PROTOCOL_WAV_M4                                         8
#define RSSCOPE_VAL_PROTOCOL_WAV_R1                                         9
#define RSSCOPE_VAL_PROTOCOL_WAV_R2                                         10
#define RSSCOPE_VAL_PROTOCOL_WAV_R3                                         11
#define RSSCOPE_VAL_PROTOCOL_WAV_R4                                         12

// rsscope_rngProtocolType
#define RSSCOPE_VAL_I2C                                                     0
#define RSSCOPE_VAL_SPI                                                     1
#define RSSCOPE_VAL_UART                                                    2
#define RSSCOPE_VAL_CAN                                                     3
#define RSSCOPE_VAL_LIN                                                     4
#define RSSCOPE_VAL_FLEX                                                    5

// rsscope_rngProtocolTechnology
#define RSSCOPE_VAL_V38                                                     0
#define RSSCOPE_VAL_V25                                                     1
#define RSSCOPE_VAL_V20                                                     2
#define RSSCOPE_VAL_V165                                                    3
#define RSSCOPE_VAL_V15                                                     4
#define RSSCOPE_VAL_V125                                                    5
#define RSSCOPE_VAL_V09                                                     6
#define RSSCOPE_VAL_V0                                                      7
#define RSSCOPE_VAL_VM13                                                    8
#define RSSCOPE_VAL_MAN                                                     9

// rsscope_rngProtocolPolarity
#define RSSCOPE_VAL_IDLE_LOW                                                0
#define RSSCOPE_VAL_IDLE_HIGH                                               1

// rsscope_rngProtocolTriggerCondition
#define RSSCOPE_VAL_COND_NQ                                                 0
#define RSSCOPE_VAL_COND_EQ                                                 1
#define RSSCOPE_VAL_COND_LT                                                 2
#define RSSCOPE_VAL_COND_LE                                                 3
#define RSSCOPE_VAL_COND_GT                                                 4
#define RSSCOPE_VAL_COND_GE                                                 5
#define RSSCOPE_VAL_COND_IN                                                 6
#define RSSCOPE_VAL_COND_OUT                                                7

// rsscope_rngProtocolI2CAddressType
#define RSSCOPE_VAL_I2C_AUTO                                                0
#define RSSCOPE_VAL_I2C_BIT7                                                1
#define RSSCOPE_VAL_I2C_BIT7_RW                                             2
#define RSSCOPE_VAL_I2C_BIT10                                               3
#define RSSCOPE_VAL_I2C_ANY                                                 4

// rsscope_rngProtocolI2CTriggerType
#define RSSCOPE_VAL_I2C_TRIGGER_START                                       0
#define RSSCOPE_VAL_I2C_TRIGGER_REPSTART                                    1
#define RSSCOPE_VAL_I2C_TRIGGER_STOP                                        2
#define RSSCOPE_VAL_I2C_TRIGGER_NACK                                        3
#define RSSCOPE_VAL_I2C_TRIGGER_ADDRESS                                     4
#define RSSCOPE_VAL_I2C_TRIGGER_ADOR                                        5
#define RSSCOPE_VAL_I2C_TRIGGER_ADAT                                        6

// rsscope_rngProtocolI2CAccessBit
#define RSSCOPE_VAL_I2C_ACCESS_BIT_UNDEF                                    -1
#define RSSCOPE_VAL_I2C_ACCESS_BIT_EITHER                                   0
#define RSSCOPE_VAL_I2C_ACCESS_BIT_READ                                     1
#define RSSCOPE_VAL_I2C_ACCESS_BIT_WRITE                                    2

// rsscope_rngProtocolSPIBitOrder
#define RSSCOPE_VAL_SPI_MSBF                                                0
#define RSSCOPE_VAL_SPI_LSBF                                                1

// rsscope_rngProtocolSPIPolarity
#define RSSCOPE_VAL_ACTLOW                                                  0
#define RSSCOPE_VAL_ACTHIGH                                                 1

// rsscope_rngProtocolSPITriggerType
#define RSSCOPE_VAL_SPI_TRIGGER_SSACTIVE                                    0
#define RSSCOPE_VAL_SPI_TRIGGER_TIMEOUT                                     1
#define RSSCOPE_VAL_SPI_TRIGGER_MOSI                                        2
#define RSSCOPE_VAL_SPI_TRIGGER_MISO                                        3
#define RSSCOPE_VAL_SPI_TRIGGER_MOMI                                        4

// rsscope_rngProtocolSPIDataAlignment
#define RSSCOPE_VAL_SPI_TRIGGER_BIT                                         0
#define RSSCOPE_VAL_SPI_TRIGGER_WORD                                        1

// rsscope_rngProtocolSPIFrameStartCond
#define RSSCOPE_VAL_SPI_FRAME_START_SS                                      0
#define RSSCOPE_VAL_SPI_FRAME_START_CLK                                     1

// rsscope_rngProtocolUARTParity
#define RSSCOPE_VAL_UART_NONE                                               0
#define RSSCOPE_VAL_UART_ODD                                                1
#define RSSCOPE_VAL_UART_EVEN                                               2
#define RSSCOPE_VAL_UART_MARK                                               3
#define RSSCOPE_VAL_UART_SPACE                                              4
#define RSSCOPE_VAL_UART_DC                                                 5

// rsscope_rngProtocolUARTStopBits
#define RSSCOPE_VAL_UART_B1                                                 0
#define RSSCOPE_VAL_UART_B1_5                                               1
#define RSSCOPE_VAL_UART_B2                                                 2

// rsscope_rngProtocolUARTTriggerType
#define RSSCOPE_VAL_UART_TRIGGER_STBT                                       0
#define RSSCOPE_VAL_UART_TRIGGER_PCKS                                       1
#define RSSCOPE_VAL_UART_TRIGGER_DATA                                       2
#define RSSCOPE_VAL_UART_TRIGGER_PRER                                       3
#define RSSCOPE_VAL_UART_TRIGGER_BRKC                                       4
#define RSSCOPE_VAL_UART_TRIGGER_FERR                                       5

// rsscope_rngProtocolUARTLine
#define RSSCOPE_VAL_UART_RX                                                 0
#define RSSCOPE_VAL_UART_TX                                                 1

// rsscope_rngProtocolUARTDataPosition
#define RSSCOPE_VAL_UART_TRIGGER_EQUAL                                      0
#define RSSCOPE_VAL_UART_TRIGGER_NEQUAL                                     1
#define RSSCOPE_VAL_UART_TRIGGER_GREATER                                    2
#define RSSCOPE_VAL_UART_TRIGGER_INRANGE                                    3

// rsscope_rngProtocolLINTechnology
#define RSSCOPE_VAL_LIN_V9                                                  0
#define RSSCOPE_VAL_LIN_V6                                                  1
#define RSSCOPE_VAL_LIN_V35                                                 2
#define RSSCOPE_VAL_LIN_V25                                                 3
#define RSSCOPE_VAL_LIN_V15                                                 4
#define RSSCOPE_VAL_LIN_MAN                                                 5

// rsscope_rngProtocolLINStandard
#define RSSCOPE_VAL_LIN_STANDARD_AUTO                                       0
#define RSSCOPE_VAL_LIN_STANDARD_1X                                         1
#define RSSCOPE_VAL_LIN_STANDARD_2X                                         2
#define RSSCOPE_VAL_LIN_STANDARD_J2602                                      3

// rsscope_rngProtocolLINTrigger
#define RSSCOPE_VAL_LIN_FRAME_START                                         0
#define RSSCOPE_VAL_LIN_FRAME_ID                                            1
#define RSSCOPE_VAL_LIN_FRAME_ID_OR                                         2
#define RSSCOPE_VAL_LIN_FRMAE_ID_DATA                                       3
#define RSSCOPE_VAL_LIN_FRAME_WAKEUP                                        4
#define RSSCOPE_VAL_LIN_ERR_COND                                            5

// rsscope_rngProtocolCANLineType
#define RSSCOPE_VAL_CAN_LOW                                                 0
#define RSSCOPE_VAL_CAN_HIGH                                                1

// rsscope_rngProtocolCANTechnology
#define RSSCOPE_VAL_CAN_V25                                                 0
#define RSSCOPE_VAL_CAN_V3                                                  1
#define RSSCOPE_VAL_CAN_V2                                                  2
#define RSSCOPE_VAL_CAN_V0                                                  3
#define RSSCOPE_VAL_CAN_MAN                                                 4

// rsscope_rngProtocolCANTriggMode
#define RSSCOPE_VAL_CAN_FRAME_START                                         0
#define RSSCOPE_VAL_CAN_FRAME_TYPE                                          1
#define RSSCOPE_VAL_CAN_MSG_ID                                              2
#define RSSCOPE_VAL_CAN_MSG_ID_DATA                                         3
#define RSSCOPE_VAL_CAN_ERR_COND                                            4

// rsscope_rngProtocolCANTriggFrameType
#define RSSCOPE_VAL_CAN_FRAME_TYPE_DATA                                     0
#define RSSCOPE_VAL_CAN_FRAME_TYPE_REMOTE                                   1
#define RSSCOPE_VAL_CAN_FRAME_TYPE_ERROR                                    2
#define RSSCOPE_VAL_CAN_FRAME_TYPE_OVER_LOAD                                3

// rsscope_rngProtocolCANIDType
#define RSSCOPE_VAL_CAN_FRAME_ID_TYPE_B11                                   0
#define RSSCOPE_VAL_CAN_FRAME_ID_TYPE_B29                                   1
#define RSSCOPE_VAL_CAN_FRAME_ID_TYPE_ANY                                   2

// rsscope_rngProtocolCANEndianness
#define RSSCOPE_VAL_CAN_FRAME_BIG_EDIAN                                     0
#define RSSCOPE_VAL_CAN_FRAME_LITTE_EDIAN                                   1

// rsscope_rngDisplayStyle
#define RSSCOPE_VAL_DISPLAY_STYLE_LINE                                      0
#define RSSCOPE_VAL_DISPLAY_STYLE_MARKER                                    1

// rsscope_rngSignalStyle
#define RSSCOPE_VAL_SIGNAL_STYLE_VECTORS                                    0
#define RSSCOPE_VAL_SIGNAL_STYLE_DOTS                                       1

// rsscope_rngSignalBarPostion
#define RSSCOPE_VAL_SIGNAL_BAR_POSITION_LEFT                                0
#define RSSCOPE_VAL_SIGNAL_BAR_POSITION_RIGHT                               1

// rsscope_rngCalibrationSourceFrequency
#define RSSCOPE_VAL_CALIBRATION_FREQUENCY_MHZ10                             0
#define RSSCOPE_VAL_CALIBRATION_FREQUENCY_GHZ1                              1

// rsscope_rngCalibrationOperatingMode
#define RSSCOPE_VAL_CALIBRATION_OPERATING_MODE_SKEW                         0
#define RSSCOPE_VAL_CALIBRATION_OPERATING_MODE_GAIN                         1

// rsscope_rngCalibrationDestination
#define RSSCOPE_VAL_CALIBRATION_DESTINATION_INTERNAL                        0
#define RSSCOPE_VAL_CALIBRATION_DESTINATION_EXTERNAL                        1

// rsscope_rngSelftestStatus
#define RSSCOPE_VAL_SELFTEST_FAILED                                         0
#define RSSCOPE_VAL_SELFTEST_PASSED                                         1
#define RSSCOPE_VAL_SELFTEST_UNDEFINED                                      2

// rsscope_rngHardcopyDevice
#define RSSCOPE_VAL_HARDCOPY_DEVICE_MEM                                     0
#define RSSCOPE_VAL_HARDCOPY_DEVICE_PRINT                                   1
#define RSSCOPE_VAL_HARDCOPY_DEVICE_CLIPBOARD                               2

// rsscope_rngHardcopyDeviceLang
#define RSSCOPE_VAL_HARDCOPY_DEVICE_LANG_PNG                                0
#define RSSCOPE_VAL_HARDCOPY_DEVICE_LANG_JPG                                1
#define RSSCOPE_VAL_HARDCOPY_DEVICE_LANG_BMP                                2
#define RSSCOPE_VAL_HARDCOPY_DEVICE_LANG_TIFF                               3

// rsscope_rngHardcopyDeviceOrientation
#define RSSCOPE_VAL_HARDCOPY_ORIENTATION_PORTRAIT                           0
#define RSSCOPE_VAL_HARDCOPY_ORIENTATION_LANDSCAPE                          1

// rsscope_rngAttUnits
#define RSSCOPE_VAL_ATT_V                                                   0
#define RSSCOPE_VAL_ATT_A                                                   1
#define RSSCOPE_VAL_ATT_W                                                   2

// rsscope_rngEATScale
#define RSSCOPE_VAL_EAT_LIN                                                 0
#define RSSCOPE_VAL_EAT_LOG                                                 1

// rsscope_rngIntExt
#define RSSCOPE_VAL_INT                                                     0
#define RSSCOPE_VAL_EXT                                                     1

// rsscope_rngDSPTriggCoupling
#define RSSCOPE_VAL_DSP_TRIGGER_OFF                                         0
#define RSSCOPE_VAL_DSP_TRIGGER_RF_REFECT                                   1

// rsscope_rngEnvelopeType
#define RSSCOPE_VAL_ENVELOPE_MIN                                            0
#define RSSCOPE_VAL_ENVELOPE_MAX                                            1
#define RSSCOPE_VAL_ENVELOPE_BOTH                                           2

// rsscope_rngPatternFormat
#define RSSCOPE_VAL_PATTERN_BIN                                             0
#define RSSCOPE_VAL_PATTERN_OCT                                             1
#define RSSCOPE_VAL_PATTERN_DEC                                             2
#define RSSCOPE_VAL_PATTERN_HEX                                             3
#define RSSCOPE_VAL_PATTERN_ASCII                                           4
#define RSSCOPE_VAL_PATTERN_STRING                                          5

// rsscope_rngWaveformExportScope
#define RSSCOPE_VAL_WAV_EXPORT_COMPLETE                                     0
#define RSSCOPE_VAL_WAV_EXPORT_ZOOM                                         1
#define RSSCOPE_VAL_WAV_EXPORT_CURSOR                                       2
#define RSSCOPE_VAL_WAV_EXPORT_GATE                                         3
#define RSSCOPE_VAL_WAV_EXPORT_MANUAL                                       4

// rsscope_rngCursor
#define RSSCOPE_VAL_CURSOR_1                                                1
#define RSSCOPE_VAL_CURSOR_2                                                2
#define RSSCOPE_VAL_CURSOR_3                                                3
#define RSSCOPE_VAL_CURSOR_4                                                4

// rsscope_rngMeasurement
#define RSSCOPE_VAL_MEAS1                                                   1
#define RSSCOPE_VAL_MEAS2                                                   2
#define RSSCOPE_VAL_MEAS3                                                   3
#define RSSCOPE_VAL_MEAS4                                                   4
#define RSSCOPE_VAL_MEAS5                                                   5
#define RSSCOPE_VAL_MEAS6                                                   6
#define RSSCOPE_VAL_MEAS7                                                   7
#define RSSCOPE_VAL_MEAS8                                                   8
#define RSSCOPE_VAL_IMEAS                                                   9

// rsscope_rngProbePredefinedCurrent
#define RSSCOPE_VAL_PROBE_FREE                                              0
#define RSSCOPE_VAL_PROBE_ZC10                                              1
#define RSSCOPE_VAL_PROBE_ZC20                                              2

// rsscope_rngProbeMeasurementType
#define RSSCOPE_VAL_PROBE_MEAS_DIFFERENTIAL                                 0
#define RSSCOPE_VAL_PROBE_MEAS_COMMONMODE                                   1

// rsscope_rngAmpRefLevSelection
#define RSSCOPE_VAL_AMPT_LEVEL_LOW                                          0
#define RSSCOPE_VAL_AMPT_LEVEL_MIDD                                         1
#define RSSCOPE_VAL_AMPT_LEVEL_UPP                                          2

// rsscope_rngAmplitudeDelayDirection
#define RSSCOPE_VAL_AMPT_DIRECTION_FRFI                                     0
#define RSSCOPE_VAL_AMPT_DIRECTION_FRLA                                     1

// rsscope_rngI2CPositionCondition
#define RSSCOPE_VAL_I2C_COND_ANY                                            0
#define RSSCOPE_VAL_I2C_COND_EQ                                             1
#define RSSCOPE_VAL_I2C_COND_GE                                             2
#define RSSCOPE_VAL_I2C_COND_RAN                                            3

// rsscope_rngSPIPositionCondition
#define RSSCOPE_VAL_SPI_COND_ANY                                            0
#define RSSCOPE_VAL_SPI_COND_EQ                                             1
#define RSSCOPE_VAL_SPI_COND_NEQ                                            2
#define RSSCOPE_VAL_SPI_COND_GE                                             3
#define RSSCOPE_VAL_SPI_COND_RAN                                            4

// rsscope_rngProtocolLINTriggerDataCondition
#define RSSCOPE_VAL_COND_LIN_DATA_EQ                                        0
#define RSSCOPE_VAL_COND_LIN_DATA_GT                                        1

// rsscope_rngLINDataTransfer
#define RSSCOPE_VAL_LIN_TRANSFER_BENDIAN                                    0
#define RSSCOPE_VAL_LIN_TRANSFER_LENDIAN                                    1

// rsscope_rngFlexRaySrcType
#define RSSCOPE_VAL_FLEXRAY_TYPE_SINGLE                                     0
#define RSSCOPE_VAL_FLEXRAY_TYPE_DIFF                                       1
#define RSSCOPE_VAL_FLEXRAY_TYPE_LOGIC                                      2

// rsscope_rngFlexRayPolarity
#define RSSCOPE_VAL_FLEXRAY_POLARITY_PLUS                                   0
#define RSSCOPE_VAL_FLEXRAY_POLARITY_MINUS                                  1

// rsscope_rngFlexRaySinglePreset
#define RSSCOPE_VAL_FLEXRAY_SINGLE_2500_150                                 0
#define RSSCOPE_VAL_FLEXRAY_SINGLE_2500_200                                 1
#define RSSCOPE_VAL_FLEXRAY_SINGLE_2500_250                                 2
#define RSSCOPE_VAL_FLEXRAY_SINGLE_2500_300                                 3
#define RSSCOPE_VAL_FLEXRAY_SINGLE_MAN                                      4

// rsscope_rngFlexRayDifferentialPreset
#define RSSCOPE_VAL_FLEXRAY_DIFF_MV150                                      0
#define RSSCOPE_VAL_FLEXRAY_DIFF_MV200                                      1
#define RSSCOPE_VAL_FLEXRAY_DIFF_MV250                                      2
#define RSSCOPE_VAL_FLEXRAY_DIFF_MV300                                      3
#define RSSCOPE_VAL_FLEXRAY_DIFF_MAN                                        4

// rsscope_rngFlexRayLogicPreset
#define RSSCOPE_VAL_FLEXRAY_LOGIC_V25                                       0
#define RSSCOPE_VAL_FLEXRAY_LOGIC_V165                                      1
#define RSSCOPE_VAL_FLEXRAY_LOGIC_V125                                      2
#define RSSCOPE_VAL_FLEXRAY_LOGIC_V09                                       3
#define RSSCOPE_VAL_FLEXRAY_LOGIC_V0                                        4
#define RSSCOPE_VAL_FLEXRAY_LOGIC_MAN                                       5

// rsscope_rngFlexRayBitRate
#define RSSCOPE_VAL_FLEXRAY_BITRATE_M10                                     0
#define RSSCOPE_VAL_FLEXRAY_BITRATE_M5                                      1
#define RSSCOPE_VAL_FLEXRAY_BITRATE_M25                                     2

// rsscope_rngFlexRayChannel
#define RSSCOPE_VAL_FLEXRAY_CHA                                             0
#define RSSCOPE_VAL_FLEXRAY_CHB                                             1

// rsscope_rngFlexRayTriggerType
#define RSSCOPE_VAL_FLEXRAY_FRAME_START                                     0
#define RSSCOPE_VAL_FLEXRAY_ID_DATA                                         1
#define RSSCOPE_VAL_FLEXRAY_SYMBOL                                          2
#define RSSCOPE_VAL_FLEXRAY_ERR_COND                                        3

// rsscope_rngFlexRayIndicatorBits
#define RSSCOPE_VAL_FLEXRAY_BITS_ZERO                                       0
#define RSSCOPE_VAL_FLEXRAY_BITS_ONE                                        1
#define RSSCOPE_VAL_FLEXRAY_BITS_DC                                         2

// rsscope_rngFlexRayCondition
#define RSSCOPE_VAL_COND_OFF                                                8

// rsscope_rngFlexRaySymbol
#define RSSCOPE_VAL_FLEXRAY_SYMBOL_CASMTS                                   0
#define RSSCOPE_VAL_FLEXRAY_SYMBOL_WAKEUP                                   1

// rsscope_rngFlexRayFrameStatus
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_OK                                  0
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_FSS                                 1
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_BSS                                 2
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_FES                                 3
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_IND                                 4
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_HCRC                                5
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_CRC                                 6
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_LENER                               7
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_WAK                                 8
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_MTS                                 9
#define RSSCOPE_VAL_FLEXRAY_FRAME_STATE_INS                                 10

// rsscope_rngFlexRayFrameType
#define RSSCOPE_VAL_FLEXRAY_FRAME_TYPE_UNKNOWN                              0
#define RSSCOPE_VAL_FLEXRAY_FRAME_TYPE_STATIC                               1
#define RSSCOPE_VAL_FLEXRAY_FRAME_TYPE_DYNAMIC                              2
#define RSSCOPE_VAL_FLEXRAY_FRAME_TYPE_WAKE                                 3
#define RSSCOPE_VAL_FLEXRAY_FRAME_TYPE_SYMBOL                               4

// rsscope_rngFlexRayFieldStatus
#define RSSCOPE_VAL_CAN_FRAME_STATE_OK                                      0
#define RSSCOPE_VAL_CAN_FRAME_STATE_UVAL                                    1
#define RSSCOPE_VAL_CAN_FRAME_STATE_INS                                     2

// rsscope_rngMSODisplayRepresentation
#define RSSCOPE_VAL_MSO_REPRESENTATION_COMBINED                             0
#define RSSCOPE_VAL_MSO_REPRESENTATION_ANALOG                               1

// rsscope_rngMSOClockSource
#define RSSCOPE_VAL_MSO_D0                                                  0
#define RSSCOPE_VAL_MSO_D1                                                  1
#define RSSCOPE_VAL_MSO_D2                                                  2
#define RSSCOPE_VAL_MSO_D3                                                  3
#define RSSCOPE_VAL_MSO_D4                                                  4
#define RSSCOPE_VAL_MSO_D5                                                  5
#define RSSCOPE_VAL_MSO_D6                                                  6
#define RSSCOPE_VAL_MSO_D7                                                  7
#define RSSCOPE_VAL_MSO_D8                                                  8
#define RSSCOPE_VAL_MSO_D9                                                  9
#define RSSCOPE_VAL_MSO_D10                                                 10
#define RSSCOPE_VAL_MSO_D11                                                 11
#define RSSCOPE_VAL_MSO_D12                                                 12
#define RSSCOPE_VAL_MSO_D13                                                 13
#define RSSCOPE_VAL_MSO_D14                                                 14
#define RSSCOPE_VAL_MSO_D15                                                 15

// rsscope_rngMSOHysteresis
#define RSSCOPE_VAL_MSO_HYSTERESIS_MAXIMUM                                  0
#define RSSCOPE_VAL_MSO_HYSTERESIS_ROBUST                                   1
#define RSSCOPE_VAL_MSO_HYSTERESIS_NORMAL                                   2

// rsscope_rngMSOTriggerType
#define RSSCOPE_VAL_MSO_EDGE_TRIGGER                                        0
#define RSSCOPE_VAL_MSO_WIDTH_TRIGGER                                       1
#define RSSCOPE_VAL_MSO_TIMEOUT_TRIGGER                                     2
#define RSSCOPE_VAL_MSO_DATA_TO_CLOCK_TRIGGER                               3
#define RSSCOPE_VAL_MSO_STATE_TRIGGER                                       4
#define RSSCOPE_VAL_MSO_PATTERN_TRIGGER                                     5
#define RSSCOPE_VAL_MSO_SERIAL_PATTERN_TRIGGER                              6

// rsscope_rngMSOTriggerSource
#define RSSCOPE_VAL_MSO_DALL                                                16
#define RSSCOPE_VAL_MSO_MSOB1                                               17
#define RSSCOPE_VAL_MSO_MSOB2                                               18
#define RSSCOPE_VAL_MSO_MSOB3                                               19
#define RSSCOPE_VAL_MSO_MSOB4                                               20

// rsscope_rngMSOTimeoutCondition
#define RSSCOPE_VAL_MSO_TIMEOUT_LOW                                         0
#define RSSCOPE_VAL_MSO_TIMEOUT_HIGH                                        1
#define RSSCOPE_VAL_MSO_TIMEOUT_EITHER                                      2

// rsscope_rngMSOTriggerChannelState
#define RSSCOPE_VAL_MSO_LOW                                                 0
#define RSSCOPE_VAL_MSO_HIGH                                                1
#define RSSCOPE_VAL_MSO_DC                                                  2

// rsscope_rngMSOPatternTimeoutMode
#define RSSCOPE_VAL_PATTERN_TIMEOUT_EITHER                                  2

// rsscope_rngProtocolI2CRWBit
#define RSSCOPE_VAL_PROTOCOL_I2C_RW_BIT_SEPARATE                            0
#define RSSCOPE_VAL_PROTOCOL_I2C_RW_BIT_IN_ADDRESS                          1

// rsscope_rngProtocolLINTriggerCRCStandard
#define RSSCOPE_VAL_LIN_CRC_STANDARD_V1X                                    0
#define RSSCOPE_VAL_LIN_CRC_STANDARD_V2X                                    1
#define RSSCOPE_VAL_LIN_CRC_STANDARD_J2602                                  2
#define RSSCOPE_VAL_LIN_CRC_STANDARD_AUTO                                   3

// rsscope_rngNFCTechnology
#define RSSCOPE_VAL_NFC_A                                                   0
#define RSSCOPE_VAL_NFC_B                                                   1
#define RSSCOPE_VAL_NFC_F                                                   2

// rsscope_rngNFCTriggerBitRate
#define RSSCOPE_VAL_NFC_BIT_RATE_106                                        0
#define RSSCOPE_VAL_NFC_BIT_RATE_212                                        1
#define RSSCOPE_VAL_NFC_BIT_RATE_424                                        2

// rsscope_rngNFCTriggerEvent
#define RSSCOPE_VAL_NFC_EVENT_ALL                                           0
#define RSSCOPE_VAL_NFC_EVENT_SENS                                          1
#define RSSCOPE_VAL_NFC_EVENT_ALLB                                          2
#define RSSCOPE_VAL_NFC_EVENT_SENSB                                         3
#define RSSCOPE_VAL_NFC_EVENT_SOS48                                         4
#define RSSCOPE_VAL_NFC_EVENT_SOS96                                         5

// rsscope_rngMathResetMode
#define RSSCOPE_VAL_MATH_RESET_NONE                                         0
#define RSSCOPE_VAL_MATH_RESET_TIME                                         1
#define RSSCOPE_VAL_MATH_RESET_WFMS                                         2

// rsscope_rngIQInputType
#define RSSCOPE_VAL_IQ_INPUT_TYPE_REAL                                      0
#define RSSCOPE_VAL_IQ_INPUT_TYPE_COMPLEX                                   1

// rsscope_rngIQInputMode
#define RSSCOPE_VAL_IQ_INPUT_MODE_BASEBAND                                  0
#define RSSCOPE_VAL_IQ_INPUT_TYPE_RFIF                                      1

// rsscope_rngIQRealSideband
#define RSSCOPE_VAL_IQ_REAL_SIDEBAND_NORMAL                                 1
#define RSSCOPE_VAL_IQ_REAL_SIDEBAND_INVERSE                                0

// rsscope_rngIQComplexSideband
#define RSSCOPE_VAL_IQ_COMPLEX_SIDEBAND_NORMAL_UPP                          0
#define RSSCOPE_VAL_IQ_COMPLEX_SIDEBAND_NORMAL_LOW                          1
#define RSSCOPE_VAL_IQ_COMPLEX_SIDEBAND_INVERSE_UPP                         2
#define RSSCOPE_VAL_IQ_COMPLEX_SIDEBAND_INVERSE_LOW                         3

// rsscope_rngConfigureTVTriggerStandard
#define RSSCOPE_VAL_TV_STANDARD_CUSTOM                                      0
#define RSSCOPE_VAL_TV_STANDARD_PAL                                         1
#define RSSCOPE_VAL_TV_STANDARD_PALM                                        2
#define RSSCOPE_VAL_TV_STANDARD_NTSC                                        3
#define RSSCOPE_VAL_TV_STANDARD_SEC                                         4
#define RSSCOPE_VAL_TV_STANDARD_P480L60HZ                                   5
#define RSSCOPE_VAL_TV_STANDARD_P720L30HZ                                   6
#define RSSCOPE_VAL_TV_STANDARD_P720L50HZ                                   7
#define RSSCOPE_VAL_TV_STANDARD_P720L60HZ                                   8
#define RSSCOPE_VAL_TV_STANDARD_I1080L50HZ                                  9
#define RSSCOPE_VAL_TV_STANDARD_I1080L60HZ                                  10
#define RSSCOPE_VAL_TV_STANDARD_P1080L24HZ                                  11
#define RSSCOPE_VAL_TV_STANDARD_P1080L24HZSF                                12
#define RSSCOPE_VAL_TV_STANDARD_P1080L25HZ                                  13
#define RSSCOPE_VAL_TV_STANDARD_P1080L30HZ                                  14
#define RSSCOPE_VAL_TV_STANDARD_P1080L50HZ                                  15
#define RSSCOPE_VAL_TV_STANDARD_P1080L60HZ                                  16

// rsscope_rngTVTriggerMode
#define RSSCOPE_VAL_TV_MODE_ALL                                             0
#define RSSCOPE_VAL_TV_MODE_ODD                                             1
#define RSSCOPE_VAL_TV_MODE_EVEN                                            2
#define RSSCOPE_VAL_TV_MODE_ALIN                                            3
#define RSSCOPE_VAL_TV_MODE_LINE                                            4

// rsscope_rngTVTriggerField
#define RSSCOPE_VAL_TV_FIELD_ODD                                            0
#define RSSCOPE_VAL_TV_FIELD_EVEN                                           1

// rsscope_rngTVTriggerPulseType
#define RSSCOPE_VAL_TV_PULSE_BI_LEVEL                                       0
#define RSSCOPE_VAL_TV_PULSE_TRI_LEVEL                                      1

// rsscope_rngTVScanMode
#define RSSCOPE_VAL_TV_SCAN_MODE_INTERLACED                                 0
#define RSSCOPE_VAL_TV_SCAN_MODE_PROGRESSIVE                                1
#define RSSCOPE_VAL_TV_SCAN_MODE_SEGMENTED                                  2

// rsscope_rngResultBoxPosition
#define RSSCOPE_VAL_RESULT_BOX_POSITION_PREVIEW                             0
#define RSSCOPE_VAL_RESULT_BOX_POSITION_FLOATING                            1
/* END GENERATE */

/*****************************************************************************
 *- Hidden Attribute Declarations -------------------------------------------*
 *****************************************************************************/

#define RSSCOPE_ATTR_OPC_TIMEOUT               (RS_ATTR_OPC_TIMEOUT)           /* ViInt32 */
#define RSSCOPE_ATTR_IO_SESSION                (RS_ATTR_IO_SESSION)            /* ViSession */
#define RSSCOPE_ATTR_OPC_CALLBACK              (RS_ATTR_OPC_CALLBACK)          /* ViAddr */
#define RSSCOPE_ATTR_CHECK_STATUS_CALLBACK     (RS_ATTR_CHECK_STATUS_CALLBACK) /* ViAddr */

/****************************************************************************
 *---------------- Constant definition  ------------------------------------*
 ****************************************************************************/
#define RSSCOPE_VAL_MASK_TEST_EVENT_BEEP     0
#define RSSCOPE_VAL_MASK_TEST_EVENT_STOP     1
#define RSSCOPE_VAL_MASK_TEST_EVENT_PRINT    2
#define RSSCOPE_VAL_MASK_TEST_EVENT_SAVE_WFM 3

#define RSSCOPE_VAL_MASK_TEST_ACTION_NOACTION  0
#define RSSCOPE_VAL_MASK_TEST_ACTION_SUCCESS   1
#define RSSCOPE_VAL_MASK_TEST_ACTION_VIOLATION 2
    
#define RSSCOPE_VAL_MASK_TEST_ACTION_CREATE 0
#define RSSCOPE_VAL_MASK_TEST_ACTION_DELETE 1
    
#define RSSCOPE_VAL_MASK_TEST_SOURCE_NONE 0
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C1W1 1
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C1W2 2
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C1W3 3
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C2W1 4
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C2W2 5
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C2W3 6
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C3W1 7
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C3W2 8
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C3W3 9
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C4W1 10
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C4W2 11
#define RSSCOPE_VAL_MASK_TEST_SOURCE_C4W3 12
#define RSSCOPE_VAL_MASK_TEST_SOURCE_M1   13
#define RSSCOPE_VAL_MASK_TEST_SOURCE_M2   14
#define RSSCOPE_VAL_MASK_TEST_SOURCE_M3   15
#define RSSCOPE_VAL_MASK_TEST_SOURCE_M4   16
#define RSSCOPE_VAL_MASK_TEST_SOURCE_R1   17
#define RSSCOPE_VAL_MASK_TEST_SOURCE_R2   18
#define RSSCOPE_VAL_MASK_TEST_SOURCE_R3   19
#define RSSCOPE_VAL_MASK_TEST_SOURCE_R4   20
    
#define RSSCOPE_VAL_MASK_SAMPLES      0
#define RSSCOPE_VAL_MASK_ACQUISITIONS 1

#define RSSCOPE_VAL_MASK_TEST_UPPER 0
#define RSSCOPE_VAL_MASK_TEST_LOWER 1
#define RSSCOPE_VAL_MASK_TEST_INNER 2
    
#define RSSCOPE_VAL_ADD     0
#define RSSCOPE_VAL_REMOVE  1
#define RSSCOPE_VAL_INSERT  2
    
#define RSSCOPE_VAL_CHANNEL_1   1
#define RSSCOPE_VAL_CHANNEL_2   2
#define RSSCOPE_VAL_CHANNEL_3   3
#define RSSCOPE_VAL_CHANNEL_4   4
#define RSSCOPE_VAL_CHANNEL_EXT 5

#define RSSCOPE_VAL_TRIGGER_A 1
#define RSSCOPE_VAL_TRIGGER_B 2
#define RSSCOPE_VAL_TRIGGER_R 3 
    
#define RSSCOPE_VAL_CUTOFF_KHZ5  0
#define RSSCOPE_VAL_CUTOFF_KHZ50 1
#define RSSCOPE_VAL_CUTOFF_MHZ50 2
    
#define RSSCOPE_VAL_CHANNEL1 1
#define RSSCOPE_VAL_CHANNEL2 2
#define RSSCOPE_VAL_CHANNEL3 3
#define RSSCOPE_VAL_CHANNEL4 4
    
#define RSSCOPE_VAL_MEASUREMENT_1 1
#define RSSCOPE_VAL_MEASUREMENT_2 2
#define RSSCOPE_VAL_MEASUREMENT_3 3
#define RSSCOPE_VAL_MEASUREMENT_4 4
#define RSSCOPE_VAL_MEASUREMENT_5 5
#define RSSCOPE_VAL_MEASUREMENT_6 6
#define RSSCOPE_VAL_MEASUREMENT_7 7
#define RSSCOPE_VAL_MEASUREMENT_8 8

#define RSSCOPE_VAL_MEASUREMENT_SOURCE_NONE 0
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C1W1 1
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C1W2 2
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C1W3 3
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C2W1 4
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C2W2 5
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C2W3 6
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C3W1 7
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C3W2 8
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C3W3 9
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C4W1 10
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C4W2 11
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_C4W3 12
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_M1   13
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_M2   14
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_M3   15
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_M4   16
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_R1   17
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_R2   18
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_R3   19
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_R4   20
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D0   21
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D1   22
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D2   23
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D3   24
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D4   25
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D5   26
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D6   27
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D7   28
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D8   29
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D9   30
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D10  31
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D11  32
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D12  33
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D13  34
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D14  35
#define RSSCOPE_VAL_MEASUREMENT_SOURCE_D15  36

#define RSSCOPE_VAL_MEASUREMENT_EVENT_BEEP     0
#define RSSCOPE_VAL_MEASUREMENT_EVENT_STOP     1
#define RSSCOPE_VAL_MEASUREMENT_EVENT_PRINT    2
#define RSSCOPE_VAL_MEASUREMENT_EVENT_SAVE_WFM 3
    
#define RSSCOPE_VAL_MEASUREMENT_ACTION_NOACTION  0
#define RSSCOPE_VAL_MEASUREMENT_ACTION_SUCCESS   1
#define RSSCOPE_VAL_MEASUREMENT_ACTION_VIOLATION 2

#define RSSCOPE_VAL_INIT_SINGLE     0
#define RSSCOPE_VAL_INIT_CONTINUOUS 1
#define RSSCOPE_VAL_INIT_FORCE      2
    
#define RSSCOPE_VAL_REG_COV  0
#define RSSCOPE_VAL_REG_TEMP 1
#define RSSCOPE_VAL_REG_LIM  2
#define RSSCOPE_VAL_REG_MARG 3
#define RSSCOPE_VAL_REG_MASK 4

#define RSSCOPE_VAL_REG_COND   0
#define RSSCOPE_VAL_REG_ENABLE 1
#define RSSCOPE_VAL_REG_EVENT  2
#define RSSCOPE_VAL_REG_NTR    3
#define RSSCOPE_VAL_REG_PTR    4
    
#define RSSCOPE_VAL_FILE_COPY    0
#define RSSCOPE_VAL_FILE_MOVE    1
#define RSSCOPE_VAL_FILE_DELETE  2
#define RSSCOPE_VAL_FILE_NEW_DIR 3
#define RSSCOPE_VAL_FILE_CDIR    4
#define RSSCOPE_VAL_FILE_RDIR    5
#define RSSCOPE_VAL_FILE_CDRIVE  6

#define RSSCOPE_VAL_MEM_SAVE    0
#define RSSCOPE_VAL_MEM_RECALL  1

#define RSSCOPE_VAL_CHANNEL1_AND_2 1
#define RSSCOPE_VAL_CHANNEL3_AND_4 2
#define RSSCOPE_VAL_CHANNEL_ALL    3

#define RSSCOPE_VAL_CURSOR_1 1
#define RSSCOPE_VAL_CURSOR_2 2
#define RSSCOPE_VAL_CURSOR_3 3
#define RSSCOPE_VAL_CURSOR_4 4
    
#define RSSCOPE_VAL_STATISTIC_ACTUAL    0
#define RSSCOPE_VAL_STATISTIC_AVG       1
#define RSSCOPE_VAL_STATISTIC_EVT_COUNT 2
#define RSSCOPE_VAL_STATISTIC_NEG_PEAK  3
#define RSSCOPE_VAL_STATISTIC_POS_PEAK  4
#define RSSCOPE_VAL_STATISTIC_RMS       5
#define RSSCOPE_VAL_STATISTIC_STD_DEV   6
#define RSSCOPE_VAL_STATISTIC_WAVEFORM  7 

#define RSSCOPE_VAL_SEARCH_PEAK  0
#define RSSCOPE_VAL_SEARCH_LEFT  1
#define RSSCOPE_VAL_SEARCH_RIGHT 2
#define RSSCOPE_VAL_SEARCH_NEXT  3

#define RSSCOPE_VAL_WAV_SELECT  0
#define RSSCOPE_VAL_WAV_OPEN    1
#define RSSCOPE_VAL_WAV_SAVE    2
#define RSSCOPE_VAL_WAV_DELETE  3

#define RSSCOPE_VAL_SEARCH_CATEGORY_TRIG    0
#define RSSCOPE_VAL_SEARCH_CATEGORY_FREQ    1

#define RSSCOPE_VAL_SEARCH_RESULT_NEXT      0
#define RSSCOPE_VAL_SEARCH_RESULT_ALL       1

#define RSSCOPE_VAL_SORT_MODE_POSITION      0
#define RSSCOPE_VAL_SORT_MODE_VALUE         1

#define RSSCOPE_VAL_COPY_FROM_A     0
#define RSSCOPE_VAL_COPY_FROM_B     1

#define RSSCOPE_VAL_SERIAL_BUS_1    1
#define RSSCOPE_VAL_SERIAL_BUS_2    2
#define RSSCOPE_VAL_SERIAL_BUS_3    3
#define RSSCOPE_VAL_SERIAL_BUS_4    4

#define RSSCOPE_VAL_BUS_1    1
#define RSSCOPE_VAL_BUS_2    2
#define RSSCOPE_VAL_BUS_3    3
#define RSSCOPE_VAL_BUS_4    4

#define RSSCOPE_VAL_I2C_SCL     0
#define RSSCOPE_VAL_I2C_SDA     1

#define RSSCOPE_VAL_I2C_EITHER     0
#define RSSCOPE_VAL_I2C_ACK        1
#define RSSCOPE_VAL_I2C_NACK       2
#define RSSCOPE_VAL_I2C_INCOMPLETE 3

#define RSSCOPE_VAL_I2C_FRAME_STATE_OK           0
#define RSSCOPE_VAL_I2C_FRAME_STATE_INCOMPLETE   1
#define RSSCOPE_VAL_I2C_FRAME_STATE_UNEXPSTOP    2
#define RSSCOPE_VAL_I2C_FRAME_STATE_INSUFFICIENT 3
#define RSSCOPE_VAL_I2C_FRAME_STATE_ADDIFFERENT  4

#define RSSCOPE_VAL_SPI_SCLK    0
#define RSSCOPE_VAL_SPI_SSEL    1
#define RSSCOPE_VAL_SPI_MISO    2
#define RSSCOPE_VAL_SPI_MOSI    3

#define RSSCOPE_VAL_SPI_FRAME_STATE_OK               0
#define RSSCOPE_VAL_SPI_FRAME_STATE_INCOMPLETE_FIRST 1
#define RSSCOPE_VAL_SPI_FRAME_STATE_INCOMPLETE_LAST  2
#define RSSCOPE_VAL_SPI_FRAME_STATE_INSUFFICIENT     3

#define RSSCOPE_VAL_UART_RX     0
#define RSSCOPE_VAL_UART_TX     1

#define RSSCOPE_VAL_UART_OK           0
#define RSSCOPE_VAL_UART_FRSTART      1
#define RSSCOPE_VAL_UART_FREND        2
#define RSSCOPE_VAL_UART_FRME         3
#define RSSCOPE_VAL_UART_STERROR      4
#define RSSCOPE_VAL_UART_SPERROR      5
#define RSSCOPE_VAL_UART_PRERROR      6
#define RSSCOPE_VAL_UART_INSUFFICIENT 7
#define RSSCOPE_VAL_UART_BREAK        8

#define RSSCOPE_VAL_LIN_FIELD_SYNC   0
#define RSSCOPE_VAL_LIN_FIELD_CHKSUM 1
    
#define RSSCOPE_VAL_LIN_FRAME_STATE_OK           0
#define RSSCOPE_VAL_LIN_FRAME_STATE_VERSION_ERR  1
#define RSSCOPE_VAL_LIN_FRAME_STATE_STOP_ERR     2
#define RSSCOPE_VAL_LIN_FRAME_STATE_PARITY_ERR   3
#define RSSCOPE_VAL_LIN_FRAME_STATE_INSUFFICIENT 4
#define RSSCOPE_VAL_LIN_FRAME_STATE_CHECKSUM     5
#define RSSCOPE_VAL_LIN_FRAME_STATE_LENGTH_ERR   6
#define RSSCOPE_VAL_LIN_FRAME_STATE_WAKEUP       7
#define RSSCOPE_VAL_LIN_FRAME_STATE_UART         8

#define RSSCOPE_VAL_LIN_STANDARD_UNKNOWN 0

#define RSSCOPE_VAL_LIN_FIELD_STATE_OK           0
#define RSSCOPE_VAL_LIN_FIELD_STATE_START_ERR    1
#define RSSCOPE_VAL_LIN_FIELD_STATE_STOP_ERR     2
#define RSSCOPE_VAL_LIN_FIELD_STATE_PARITY_ERR   3
#define RSSCOPE_VAL_LIN_FIELD_STATE_INSUFFICIENT 4
#define RSSCOPE_VAL_LIN_FIELD_STATE_UVAL         5

#define RSSCOPE_VAL_CAN_FIELD_DLC 0
#define RSSCOPE_VAL_CAN_FIELD_CRC 1
#define RSSCOPE_VAL_CAN_FIELD_ACK 2

#define RSSCOPE_VAL_CAN_FRAME_STATE_OK           0
#define RSSCOPE_VAL_CAN_FRAME_STATE_BIT_STUFF    1
#define RSSCOPE_VAL_CAN_FRAME_STATE_CRC_DELIM    2
#define RSSCOPE_VAL_CAN_FRAME_STATE_CRC          3
#define RSSCOPE_VAL_CAN_FRAME_STATE_END_ERR      4
#define RSSCOPE_VAL_CAN_FRAME_STATE_NO_ACK       5
#define RSSCOPE_VAL_CAN_FRAME_STATE_INSUFFICIENT 6

#define RSSCOPE_VAL_CAN_FRAME_STATE_OK        0
#define RSSCOPE_VAL_CAN_FRAME_STATE_UNDEFINED 1

#define RSSCOPE_VAL_DIAGRAM_NONE       0
#define RSSCOPE_VAL_DIAGRAM_HORIZONTAL 1
#define RSSCOPE_VAL_DIAGRAM_VERTICAL   2
#define RSSCOPE_VAL_DIAGRAM_NEW_TAB    3

#define RSSCOPE_VAL_HARDCOPY_DESTINATION_PNG  0
#define RSSCOPE_VAL_HARDCOPY_DESTINATION_JPG  1
#define RSSCOPE_VAL_HARDCOPY_DESTINATION_BMP  2
#define RSSCOPE_VAL_HARDCOPY_DESTINATION_TIFF 3
#define RSSCOPE_VAL_HARDCOPY_DESTINATION_CLP  4
#define RSSCOPE_VAL_HARDCOPY_DESTINATION_PRN  5

#define RSSCOPE_VAL_HISTOGRAM_VERTICAL   0
#define RSSCOPE_VAL_HISTOGRAM_HORIZONTAL 1

#define RSSCOPE_VAL_REF_LEVEL_MEAS_BINN 0
#define RSSCOPE_VAL_REF_LEVEL_MEAS_BOUT 1
#define RSSCOPE_VAL_REF_LEVEL_MEAS_LOW  2
#define RSSCOPE_VAL_REF_LEVEL_MEAS_MIDD 3
#define RSSCOPE_VAL_REF_LEVEL_MEAS_UPP  4
#define RSSCOPE_VAL_REF_LEVEL_MEAS_SIGH 5
#define RSSCOPE_VAL_REF_LEVEL_MEAS_SIGL 6
#define RSSCOPE_VAL_REF_LEVEL_MEAS_TINN 7
#define RSSCOPE_VAL_REF_LEVEL_MEAS_TOUT 8

#define RSSCOPE_VAL_TS_ABS 0
#define RSSCOPE_VAL_TS_REL 1

#define RSSCOPE_VAL_FLEXRAY_FIELD_FLAGS       0
#define RSSCOPE_VAL_FLEXRAY_FIELD_PAY_LENGTH  1
#define RSSCOPE_VAL_FLEXRAY_FIELD_FRAME_ID    2
#define RSSCOPE_VAL_FLEXRAY_FIELD_HCRC        3
#define RSSCOPE_VAL_FLEXRAY_FIELD_FCRC        4

#define RSSCOPE_VAL_FLEXRAY_SOURCE_DATA    0
#define RSSCOPE_VAL_FLEXRAY_SOURCE_ENABLE  1

#define RSSCOPE_VAL_AMPT_SLOPE_PULSE    0
#define RSSCOPE_VAL_AMPT_SLOPE_EDGE     1
#define RSSCOPE_VAL_AMPT_SLOPE_CLOCK    2 

#define RSSCOPE_VAL_AMPT_REF_TYPE_CLOCK 0
#define RSSCOPE_VAL_AMPT_REF_TYPE_DATA  1

#define RSSCOPE_VAL_MASK_TEST_TYPE_USER      0
#define RSSCOPE_VAL_MASK_TEST_TYPE_WAVEFORM  1

#define RSSCOPE_VAL_MASK_TEST_REFERENCE1  1
#define RSSCOPE_VAL_MASK_TEST_REFERENCE2  2
#define RSSCOPE_VAL_MASK_TEST_REFERENCE3  3
#define RSSCOPE_VAL_MASK_TEST_REFERENCE4  4

#define RSSCOPE_VAL_CLOCK_SOURCE_C1W1 1
#define RSSCOPE_VAL_CLOCK_SOURCE_C2W1 2
#define RSSCOPE_VAL_CLOCK_SOURCE_C3W1 3
#define RSSCOPE_VAL_CLOCK_SOURCE_C4W1 4

#define RSSCOPE_VAL_UART_PACKETS_NONE 0

/****************************************************************************
*---------------- Instrument Driver Function Declarations -----------------*
 ****************************************************************************/

ViStatus _VI_FUNC rsscope_init (ViRsrc resourceName, ViBoolean IDQuery,
                                ViBoolean resetDevice, ViSession* instrumentHandle);
ViStatus _VI_FUNC rsscope_InitWithOptions (ViRsrc resourceName, ViBoolean IDQuery,
                                           ViBoolean resetDevice,
                                           ViChar _VI_FAR optionString[],
                                           ViSession* instrumentHandle);
ViStatus _VI_FUNC rsscope_Autoset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureAcquisitionType (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViInt32 waveform,
                                                    ViInt32 acquisitionType);
ViStatus _VI_FUNC rsscope_ConfigureAcquisitionRecord (ViSession instrumentHandle,
                                                      ViReal64 timePerRecord,
                                                      ViReal64 acquisitionStartTime_Offset);
ViStatus _VI_FUNC rsscope_ConfigureTimeBase (ViSession instrumentHandle,
                                             ViReal64 timeScale,
                                             ViInt32 referencePoint,
                                             ViBoolean restrictOffset);
ViStatus _VI_FUNC rsscope_ConfigureRollMode (ViSession instrumentHandle,
                                             ViInt32 mode, ViInt32 minRollModeGain);
ViStatus _VI_FUNC rsscope_QueryDivisions (ViSession instrumentHandle,
                                          ViInt32* divisions);
ViStatus _VI_FUNC rsscope_ConfigureTimeSelectDependency (ViSession instrumentHandle,
                                                         ViInt32 timeSelectDependency);
ViStatus _VI_FUNC rsscope_ConfigureSampleRate (ViSession instrumentHandle,
                                               ViReal64 resolution);
ViStatus _VI_FUNC rsscope_ConfigureResolution (ViSession instrumentHandle,
                                               ViReal64 resolution);
ViStatus _VI_FUNC rsscope_QueryADCSampleRate (ViSession instrumentHandle,
                                              ViReal64* ADCSampleRate);
ViStatus _VI_FUNC rsscope_ConfigureRecordLength (ViSession instrumentHandle,
                                                 ViInt32 recordLength);
ViStatus _VI_FUNC rsscope_ConfigureRecordLengthLimit (ViSession instrumentHandle,
                                                      ViInt32 lengthLimit);
ViStatus _VI_FUNC rsscope_ConfigureAcquisitionTime (ViSession instrumentHandle,
                                                    ViReal64 acquisitionTime);
ViStatus _VI_FUNC rsscope_ConfigureResolutionEnhancement (ViSession instrumentHandle,
                                                          ViInt32 resolutionEnhancement);
ViStatus _VI_FUNC rsscope_ConfigureInterpolation (ViSession instrumentHandle,
                                                  ViInt32 interpolation);
ViStatus _VI_FUNC rsscope_ConfigureWaveformState (ViSession instrumentHandle,
                                                  ViInt32 channel, ViInt32 waveform,
                                                  ViBoolean enableWaveform);
ViStatus _VI_FUNC rsscope_ConfigureWaveformArithmetic (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViInt32 waveform,
                                                       ViInt32 arithmetic);
ViStatus _VI_FUNC rsscope_ConfigureNumberOfAverages (ViSession instrumentHandle,
                                                     ViInt32 numberOfAverages);
ViStatus _VI_FUNC rsscope_ConfigureUltraSegmentation (ViSession instrumentHandle,
                                                      ViBoolean ultraSegmentationEnabled,
                                                      ViBoolean ultraSegmentationDependecy);
ViStatus _VI_FUNC rsscope_ConfigureUltraSegmentationAutoReplay
             (ViSession instrumentHandle, ViBoolean autoReplay);
ViStatus _VI_FUNC rsscope_ConfigureChannel (ViSession instrumentHandle,
                                            ViInt32 channel,
                                            ViBoolean channelEnabled,
                                            ViReal64 verticalRange,
                                            ViReal64 verticalOffset,
                                            ViInt32 verticalCoupling);
ViStatus _VI_FUNC rsscope_ConfigureChannelGroundConnection
             (ViSession instrumentHandle, ViInt32 channel,
              ViBoolean groundConnection);
ViStatus _VI_FUNC rsscope_ConfigureChannelOffset (ViSession instrumentHandle,
                                                  ViInt32 channel, ViReal64 offset);
ViStatus _VI_FUNC rsscope_ConfigureChannelVerticalScale (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViReal64 verticalScale);
ViStatus _VI_FUNC rsscope_ConfigureChannelBandwidth (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViInt32 bandwidth);
ViStatus _VI_FUNC rsscope_ConfigureChannelMeasurementImpedance
             (ViSession instrumentHandle, ViInt32 channel, ViReal64 inputImpedance);
ViStatus _VI_FUNC rsscope_ConfigureChannelOverload (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViBoolean overload);
ViStatus _VI_FUNC rsscope_ConfigureChannelDigitalFilter (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViBoolean enable,
                                                         ViReal64 cutOff);
ViStatus _VI_FUNC rsscope_ConfigureChannelDigitalFilterTrigger
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 channel,
              ViInt32 coupling, ViReal64 RFRejectBW);
ViStatus _VI_FUNC rsscope_ConfigureChannelExternalAttenuation
             (ViSession instrumentHandle, ViInt32 channel, ViInt32 scale,
              ViReal64 attenuation);
ViStatus _VI_FUNC rsscope_ConfigureProbe (ViSession instrumentHandle,
                                          ViInt32 channel, ViBoolean channelVisible,
                                          ViReal64 offset);
ViStatus _VI_FUNC rsscope_QueryProbeState (ViSession instrumentHandle,
                                           ViInt32 channel, ViInt32* state);
ViStatus _VI_FUNC rsscope_QueryProbeCharacteristics (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViInt32 bufferSize,
                                                     ViChar _VI_FAR type[],
                                                     ViChar _VI_FAR name[],
                                                     ViReal64* inputImpedance,
                                                     ViReal64* inputCapacitance,
                                                     ViChar _VI_FAR attenuation[],
                                                     ViReal64* bandwidth);
ViStatus _VI_FUNC rsscope_ConfigureProbeMicroButtonAction
             (ViSession instrumentHandle, ViInt32 channel,
              ViInt32 microButtonAction);
ViStatus _VI_FUNC rsscope_ConfigureProbeMeasurementType (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViInt32 measurementType);
ViStatus _VI_FUNC rsscope_ProbeAutoZero (ViSession instrumentHandle,
                                         ViInt32 channel);
ViStatus _VI_FUNC rsscope_ProbeSetOffsetToMean (ViSession instrumentHandle,
                                                ViInt32 channel);
ViStatus _VI_FUNC rsscope_QueryProbeAttributes (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 bufferSize,
                                                ViChar _VI_FAR softwareVersion[],
                                                ViChar _VI_FAR productionDate[],
                                                ViChar _VI_FAR partNumber[],
                                                ViChar _VI_FAR serialNumber[]);
ViStatus _VI_FUNC rsscope_ConfigureProbeFirmwarePath (ViSession instrumentHandle,
                                                      ViInt32 channel,
                                                      ViString firmwarePath);
ViStatus _VI_FUNC rsscope_UpdateProbeFirmware (ViSession instrumentHandle,
                                               ViInt32 channel);
ViStatus _VI_FUNC rsscope_QueryProbeFirmwareUpdateStatus (ViSession instrumentHandle,
                                                          ViInt32 channel,
                                                          ViInt32* firmwareUpdateStatus);
ViStatus _VI_FUNC rsscope_ProbeSelftest (ViSession instrumentHandle,
                                         ViInt32 channel);
ViStatus _VI_FUNC rsscope_QueryProbeSelftestResult (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViInt32 bufferSize,
                                                    ViChar _VI_FAR selftestResult[]);
ViStatus _VI_FUNC rsscope_QueryProbeSelftestStatus (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViInt32* selftestStatus);
ViStatus _VI_FUNC rsscope_ConfigureProbeDetection (ViSession instrumentHandle,
                                                   ViInt32 channel, ViInt32 mode);
ViStatus _VI_FUNC rsscope_ConfigureProbeAttenuation (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViInt32 verticalUnit,
                                                     ViReal64 attenuation);
ViStatus _VI_FUNC rsscope_ConfigureProbeGain (ViSession instrumentHandle,
                                              ViInt32 channel, ViReal64 gain);
ViStatus _VI_FUNC rsscope_ConfigureCurrentProbePredefined
             (ViSession instrumentHandle, ViInt32 channel, ViInt32 predefinedProbe);
ViStatus _VI_FUNC rsscope_ConfigureCalibration (ViSession instrumentHandle,
                                                ViInt32 sourceFrequency,
                                                ViInt32 operatingMode,
                                                ViInt32 destination);
ViStatus _VI_FUNC rsscope_ConfigureReferenceOscillator (ViSession instrumentHandle,
                                                        ViBoolean useExternalReference,
                                                        ViReal64 externalReference);
ViStatus _VI_FUNC rsscope_ConfigureSkew (ViSession instrumentHandle,
                                         ViInt32 channel, ViBoolean useSkewOffset,
                                         ViReal64 skewOffset);
ViStatus _VI_FUNC rsscope_ConfigureTrigger (ViSession instrumentHandle,
                                            ViInt32 trigger, ViInt32 triggerType);
ViStatus _VI_FUNC rsscope_ConfigureTriggerCoupling (ViSession instrumentHandle,
                                                    ViInt32 trigger,
                                                    ViBoolean eventCoupling,
                                                    ViBoolean sourceCoupling);
ViStatus _VI_FUNC rsscope_ConfigureTriggerModifier (ViSession instrumentHandle,
                                                    ViInt32 trigger,
                                                    ViInt32 triggerModifier);
ViStatus _VI_FUNC rsscope_TriggerLevelAutoFind (ViSession instrumentHandle,
                                                ViInt32 trigger);
ViStatus _VI_FUNC rsscope_ConfigureRobustTriggerState (ViSession instrumentHandle,
                                                       ViInt32 trigger,
                                                       ViBoolean robustTriggerState);
ViStatus _VI_FUNC rsscope_ConfigureTriggerChannelLevel (ViSession instrumentHandle,
                                                        ViInt32 trigger,
                                                        ViInt32 channel,
                                                        ViReal64 triggerLevel);
ViStatus _VI_FUNC rsscope_ConfigureEdgeTriggerSource (ViSession instrumentHandle,
                                                      ViInt32 trigger,
                                                      ViInt32 triggerSource,
                                                      ViReal64 triggerLevel,
                                                      ViInt32 triggerSlope);
ViStatus _VI_FUNC rsscope_ConfigureEdgeExternalTrigger (ViSession instrumentHandle,
                                                        ViInt32 coupling,
                                                        ViInt32 filter,
                                                        ViInt32 cutOffFrequency);
ViStatus _VI_FUNC rsscope_ConfigureEdgeExternalTriggerGround
             (ViSession instrumentHandle, ViBoolean connectToGround);
ViStatus _VI_FUNC rsscope_ConfigureRuntTriggerSource (ViSession instrumentHandle,
                                                      ViInt32 trigger,
                                                      ViInt32 triggerSource,
                                                      ViReal64 runtLowThreshold,
                                                      ViReal64 runtHighThreshold,
                                                      ViInt32 runtPolarity);
ViStatus _VI_FUNC rsscope_ConfigureRuntTriggerRange (ViSession instrumentHandle,
                                                     ViInt32 trigger,
                                                     ViReal64 runtWidth,
                                                     ViReal64 runtDelta,
                                                     ViInt32 runtCondition);
ViStatus _VI_FUNC rsscope_ConfigureGlitchTriggerSource (ViSession instrumentHandle,
                                                        ViInt32 trigger,
                                                        ViInt32 triggerSource,
                                                        ViReal64 triggerLevel,
                                                        ViReal64 glitchWidth,
                                                        ViInt32 glitchPolarity,
                                                        ViInt32 glitchCondition);
ViStatus _VI_FUNC rsscope_ConfigureWidthTriggerSource (ViSession instrumentHandle,
                                                       ViInt32 trigger,
                                                       ViInt32 triggerSource,
                                                       ViReal64 triggerLevel,
                                                       ViReal64 width,
                                                       ViReal64 widthDelta,
                                                       ViInt32 widthPolarity,
                                                       ViInt32 widthCondition);
ViStatus _VI_FUNC rsscope_ConfigureWindowTriggerSource (ViSession instrumentHandle,
                                                        ViInt32 trigger,
                                                        ViInt32 triggerSource,
                                                        ViReal64 windowLowerLimit,
                                                        ViReal64 windowUpperLimit,
                                                        ViReal64 windowWidth,
                                                        ViReal64 windowDelta,
                                                        ViInt32 windowCondition);
ViStatus _VI_FUNC rsscope_ConfigureTimeoutTriggerSource (ViSession instrumentHandle,
                                                         ViInt32 trigger,
                                                         ViInt32 triggerSource,
                                                         ViReal64 triggerLevel,
                                                         ViReal64 timeoutValue,
                                                         ViInt32 timeoutCondition);
ViStatus _VI_FUNC rsscope_ConfigureIntervalTriggerSource (ViSession instrumentHandle,
                                                          ViInt32 trigger,
                                                          ViInt32 triggerSource,
                                                          ViReal64 triggerLevel,
                                                          ViReal64 intervalWidth,
                                                          ViReal64 intervalDelta,
                                                          ViInt32 intervalPolarity,
                                                          ViInt32 intervalCondition);
ViStatus _VI_FUNC rsscope_ConfigureSlewRateTriggerSource (ViSession instrumentHandle,
                                                          ViInt32 trigger,
                                                          ViInt32 triggerSource,
                                                          ViReal64 slewRateLowerLimit,
                                                          ViReal64 slewRateUpperLimit,
                                                          ViInt32 slewRatePolarity,
                                                          ViInt32 slewRateCondition);
ViStatus _VI_FUNC rsscope_ConfigureSlewRateTriggerRange (ViSession instrumentHandle,
                                                         ViInt32 trigger,
                                                         ViReal64 slewRate,
                                                         ViReal64 slewRateDelta);
ViStatus _VI_FUNC rsscope_ConfigureData2ClockTriggerSource
             (ViSession instrumentHandle, ViInt32 triggerSource, ViReal64 dataLevel,
              ViInt32 clockSource, ViReal64 clockLevel, ViReal64 holdTime,
              ViReal64 setupTime, ViInt32 data2ClockPolarity);
ViStatus _VI_FUNC rsscope_ConfigurePatternTriggerSource (ViSession instrumentHandle,
                                                         ViInt32 patternMode,
                                                         ViInt32 timeoutCondition,
                                                         ViReal64 timeout,
                                                         ViReal64 patternWidth,
                                                         ViReal64 patternDelta,
                                                         ViInt32 patternCondition);
ViStatus _VI_FUNC rsscope_ConfigureSerialPatternTriggerSource
             (ViSession instrumentHandle, ViInt32 triggerSource, ViReal64 dataLevel,
              ViInt32 clockSource, ViReal64 clockLevel, ViString pattern,
              ViInt32 patternPolarity);
ViStatus _VI_FUNC rsscope_ConfigureSerialBusTriggerSource
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32 protocol);
ViStatus _VI_FUNC rsscope_ConfigureNFCTrigger (ViSession instrumentHandle,
                                               ViInt32 triggerSource,
                                               ViInt32 technology, ViInt32 bitRate,
                                               ViInt32 event,
                                               ViReal64 triggerLevel);
ViStatus _VI_FUNC rsscope_ConfigureTVTrigger (ViSession instrumentHandle,
                                              ViInt32 triggerSource,
                                              ViInt32 standard, ViInt32 mode,
                                              ViInt32 lineNumber, ViInt32 lineField,
                                              ViReal64 triggerLevel,
                                              ViInt32 signalPolarity);
ViStatus _VI_FUNC rsscope_ConfigureTVTriggerCustomSettings
             (ViSession instrumentHandle, ViInt32 pulseType, ViReal64 linePeriod,
              ViReal64 pulseWidth, ViInt32 scanMode);
ViStatus _VI_FUNC rsscope_ConfigureNoiseReject (ViSession instrumentHandle,
                                                ViInt32 trigger,
                                                ViInt32 triggerSource,
                                                ViInt32 hysteresisMode,
                                                ViReal64 absoluteHysteresis);
ViStatus _VI_FUNC rsscope_ConfigureTriggerLinesDisplay (ViSession instrumentHandle,
                                                        ViBoolean showTriggerLinesPermanently);
ViStatus _VI_FUNC rsscope_ConfigureTriggerOutSignal (ViSession instrumentHandle,
                                                     ViBoolean enable,
                                                     ViInt32 polarity,
                                                     ViReal64 pulseLength);
ViStatus _VI_FUNC rsscope_QueryTriggerOutDelay (ViSession instrumentHandle,
                                                ViReal64* delay);
ViStatus _VI_FUNC rsscope_ConfigureTriggerQualification (ViSession instrumentHandle,
                                                         ViInt32 triggerType,
                                                         ViInt32 trigger,
                                                         ViBoolean qualificationEnabled,
                                                         ViInt32 channel,
                                                         ViBoolean channelEnabled,
                                                         ViInt32 channelLogic);
ViStatus _VI_FUNC rsscope_ConfigureTriggerQualificationMulitchannelLogic
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 triggerType,
              ViBoolean qualificationEnabled, ViInt32 channelCombination,
              ViInt32 multichannelLogic);
ViStatus _VI_FUNC rsscope_ConfigureAOnlyTriggerSequence (ViSession instrumentHandle,
                                                         ViInt32 holdoffMode,
                                                         ViReal64 holdoffTime,
                                                         ViInt32 holdoffEvents,
                                                         ViReal64 randomMinTime,
                                                         ViReal64 randomMaxTime);
ViStatus _VI_FUNC rsscope_QueryAOnlyTriggerSequenceAutoTimeResult
             (ViSession instrumentHandle, ViReal64* autoTime);
ViStatus _VI_FUNC rsscope_TriggerSequenceHoldoffAutoScale
             (ViSession instrumentHandle, ViReal64 autoScale);
ViStatus _VI_FUNC rsscope_ConfigureABRTriggerSequence (ViSession instrumentHandle,
                                                       ViBoolean eventCoupling,
                                                       ViReal64 sequenceDelay,
                                                       ViInt32 bEventsCount,
                                                       ViBoolean resetByTimeoutEnabled,
                                                       ViReal64 resetTimeout,
                                                       ViBoolean resetByEventEnabled);
ViStatus _VI_FUNC rsscope_ConfigurePersistence (ViSession instrumentHandle,
                                                ViBoolean enable,
                                                ViBoolean infinite, ViReal64 time);
ViStatus _VI_FUNC rsscope_ResetPersistence (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureSignalStyle (ViSession instrumentHandle,
                                                ViInt32 intensity, ViInt32 style);
ViStatus _VI_FUNC rsscope_ConfigureColorTableAssignment (ViSession instrumentHandle,
                                                         ViInt32 source,
                                                         ViBoolean useColorTable,
                                                         ViString tableName);
ViStatus _VI_FUNC rsscope_AddColorTable (ViSession instrumentHandle,
                                         ViString tableName);
ViStatus _VI_FUNC rsscope_RemoveColorTable (ViSession instrumentHandle,
                                            ViString tableName);
ViStatus _VI_FUNC rsscope_ColorTableAppendRow (ViSession instrumentHandle,
                                               ViString tableName);
ViStatus _VI_FUNC rsscope_ColorTableInsertRow (ViSession instrumentHandle,
                                               ViString tableName, ViInt32 index);
ViStatus _VI_FUNC rsscope_ColorTableDefineRow (ViSession instrumentHandle,
                                               ViString tableName, ViInt32 index,
                                               ViReal64 cumulativePercentage,
                                               ViInt32 color);
ViStatus _VI_FUNC rsscope_ColorTableRemoveRow (ViSession instrumentHandle,
                                               ViString tableName, ViInt32 index);
ViStatus _VI_FUNC rsscope_QueryColorTableCount (ViSession instrumentHandle,
                                                ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryColorTableRowCount (ViSession instrumentHandle,
                                                   ViString tableName,
                                                   ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryColorTableRow (ViSession instrumentHandle,
                                              ViString tableName, ViInt32 index,
                                              ViReal64* cumulativePercentage,
                                              ViInt32* color);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementDiagram (ViSession instrumentHandle,
                                                       ViBoolean showGrid,
                                                       ViBoolean showCrosshair,
                                                       ViBoolean showLabels,
                                                       ViBoolean showTabsAlways,
                                                       ViBoolean yGridFixed);
ViStatus _VI_FUNC rsscope_ShowSignalBar (ViSession instrumentHandle,
                                         ViBoolean enable, ViInt32 position);
ViStatus _VI_FUNC rsscope_ConfigureSignalBarAutoHide (ViSession instrumentHandle,
                                                      ViBoolean autoHide,
                                                      ViBoolean hideHead,
                                                      ViReal64 hideAfter,
                                                      ViReal64 hidingOpacity);
ViStatus _VI_FUNC rsscope_ConfigureSignalBarColor (ViSession instrumentHandle,
                                                   ViInt32 borderColor,
                                                   ViInt32 fillColor);
ViStatus _VI_FUNC rsscope_ConfigureResultBoxPosition (ViSession instrumentHandle,
                                                      ViInt32 position);
ViStatus _VI_FUNC rsscope_AddDiagram (ViSession instrumentHandle,
                                      ViString existingDiagram,
                                      ViInt32 newDiagramPosition,
                                      ViBoolean insertBefore, ViInt32 source,
                                      ViString newDiagramName);
ViStatus _VI_FUNC rsscope_DisplayDiagram (ViSession instrumentHandle,
                                          ViString diagramName);
ViStatus _VI_FUNC rsscope_RemoveDiagram (ViSession instrumentHandle,
                                         ViString diagramName);
ViStatus _VI_FUNC rsscope_ShowWaveformInDiagram (ViSession instrumentHandle,
                                                 ViString diagramName,
                                                 ViInt32 source);
ViStatus _VI_FUNC rsscope_AddWaveformToDiagram (ViSession instrumentHandle,
                                                ViString diagramName,
                                                ViInt32 source,
                                                ViBoolean assignToXAxis);
ViStatus _VI_FUNC rsscope_RemoveWaveformFromDiagram (ViSession instrumentHandle,
                                                     ViInt32 source);
ViStatus _VI_FUNC rsscope_AddDiagramZoom (ViSession instrumentHandle,
                                          ViString diagramName,
                                          ViInt32 newDiagramPosition,
                                          ViBoolean insertBefore,
                                          ViString newZoomDiagramName,
                                          ViReal64 xStart, ViReal64 xStop,
                                          ViReal64 yStart, ViReal64 yStop);
ViStatus _VI_FUNC rsscope_AddDiagramZoomCoupled (ViSession instrumentHandle,
                                                 ViString diagramName,
                                                 ViString newZoomDiagramName,
                                                 ViReal64 xOffset,
                                                 ViReal64 yOffset);
ViStatus _VI_FUNC rsscope_RemoveDiagramZoom (ViSession instrumentHandle,
                                             ViString diagramName,
                                             ViString zoomDiagramName);
ViStatus _VI_FUNC rsscope_ConfigureDiagramZoomVerticalStartStop
             (ViSession instrumentHandle, ViString diagramName,
              ViString zoomDiagramName, ViInt32 mode, ViReal64 start,
              ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureDiagramZoomHorizontalStartStop
             (ViSession instrumentHandle, ViString diagramName,
              ViString zoomDiagramName, ViInt32 mode, ViReal64 start,
              ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureDiagramZoomVerticalPositionRange
             (ViSession instrumentHandle, ViString diagramName,
              ViString zoomDiagramName, ViInt32 mode, ViReal64 position,
              ViReal64 range);
ViStatus _VI_FUNC rsscope_ConfigureDiagramZoomHorizontalPositionRange
             (ViSession instrumentHandle, ViString diagramName,
              ViString zoomDiagramName, ViInt32 mode, ViReal64 position,
              ViReal64 range);
ViStatus _VI_FUNC rsscope_ConfigureXYDiagram (ViSession instrumentHandle,
                                              ViInt32 XYDiagramNumber,
                                              ViBoolean XYDiagramState,
                                              ViBoolean constantXYRatio,
                                              ViInt32 xSource, ViInt32 ySource);
ViStatus _VI_FUNC rsscope_SwapXYDiagram (ViSession instrumentHandle,
                                         ViInt32 XYDiagramNumber);
ViStatus _VI_FUNC rsscope_ConfigureHistoryState (ViSession instrumentHandle,
                                                 ViInt32 channel, ViInt32 waveform,
                                                 ViBoolean enableHistory);
ViStatus _VI_FUNC rsscope_ConfigureHistoryStartStop (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViInt32 waveform,
                                                     ViInt32 start, ViInt32 stop);
ViStatus _VI_FUNC rsscope_ConfigureHistoryAcquisitionView
             (ViSession instrumentHandle, ViInt32 channel, ViInt32 waveform,
              ViInt32 acquisition);
ViStatus _VI_FUNC rsscope_ConfigureHistoryAcquisitionTime
             (ViSession instrumentHandle, ViInt32 channel, ViInt32 waveform,
              ViReal64 timePerAcquisition);
ViStatus _VI_FUNC rsscope_ConfigureHistoryAutoRepeat (ViSession instrumentHandle,
                                                      ViInt32 channel,
                                                      ViInt32 waveform,
                                                      ViBoolean autoRepeat);
ViStatus _VI_FUNC rsscope_HistoryPlaybackControl (ViSession instrumentHandle,
                                                  ViInt32 channel,
                                                  ViInt32 waveform);
ViStatus _VI_FUNC rsscope_QueryHistoryTimeStamp (ViSession instrumentHandle,
                                                 ViInt32 channel, ViInt32 waveform,
                                                 ViInt32 mode, ViInt32 bufferSize,
                                                 ViChar _VI_FAR timeStamp[]);
ViStatus _VI_FUNC rsscope_QueryHistoryDate (ViSession instrumentHandle,
                                            ViInt32 channel, ViInt32 waveform,
                                            ViInt32 bufferSize,
                                            ViChar _VI_FAR date[]);
ViStatus _VI_FUNC rsscope_QueryHistoryAcquisitionsCount (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViInt32* count);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementState (ViSession instrumentHandle,
                                                     ViInt32 measurement,
                                                     ViBoolean measurementState);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementSource (ViSession instrumentHandle,
                                                      ViInt32 measurement,
                                                      ViInt32 signalSource,
                                                      ViInt32 signalSource2);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementLimitCheck (ViSession instrumentHandle,
                                                          ViInt32 measurement,
                                                          ViInt32 limitCheck);
ViStatus _VI_FUNC rsscope_ConfigureMultipleMeasurement (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViBoolean multipleMeasurement);
ViStatus _VI_FUNC rsscope_ConfigureMultipleMeasurementNumber
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementCount);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementCategory (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViInt32 category);
ViStatus _VI_FUNC rsscope_EnableAdditionalMeasurements (ViSession instrumentHandle,
                                                        ViInt32 measurement);
ViStatus _VI_FUNC rsscope_DisableAdditionalMeasurements (ViSession instrumentHandle,
                                                         ViInt32 measurement);
ViStatus _VI_FUNC rsscope_ClearMeasurementStatisticData (ViSession instrumentHandle,
                                                         ViInt32 measurement);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementEventActions
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 event,
              ViInt32 action);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementDisplayIntermediateResults
             (ViSession instrumentHandle, ViInt32 measurement,
              ViBoolean displayResultLines, ViBoolean displayReferenceLevels);
ViStatus _VI_FUNC rsscope_ConfigureMeasurementDisplayStyle
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 displayStyle);
ViStatus _VI_FUNC rsscope_ReadMeasurementResults (ViSession instrumentHandle,
                                                  ViInt32 measurement,
                                                  ViInt32 arraySize,
                                                  ViReal64 _VI_FAR results[],
                                                  ViInt32* actualPoints);
ViStatus _VI_FUNC rsscope_ConfigureCursor (ViSession instrumentHandle,
                                           ViInt32 cursor, ViBoolean cursorState,
                                           ViInt32 source, ViInt32 type);
ViStatus _VI_FUNC rsscope_AllCursorsOff (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureCursorPosition (ViSession instrumentHandle,
                                                   ViInt32 cursor,
                                                   ViReal64 xPosition1,
                                                   ViReal64 xPosition2,
                                                   ViReal64 yPosition1,
                                                   ViReal64 yPosition2);
ViStatus _VI_FUNC rsscope_ConfigureCursorCoupling (ViSession instrumentHandle,
                                                   ViInt32 cursor,
                                                   ViBoolean xCoupling,
                                                   ViBoolean yCoupling);
ViStatus _VI_FUNC rsscope_ConfigureCursorWaveformTracking
             (ViSession instrumentHandle, ViInt32 cursor, ViBoolean tracking);
ViStatus _VI_FUNC rsscope_ConfigureCursorEnvelopeWaveformSelection
             (ViSession instrumentHandle, ViInt32 cursor,
              ViInt32 firstCursorPosition, ViInt32 secondCursorPosition);
ViStatus _VI_FUNC rsscope_QueryCursorDistance (ViSession instrumentHandle,
                                               ViInt32 cursor, ViInt32 direction,
                                               ViReal64* cursorDistance);
ViStatus _VI_FUNC rsscope_QueryCursorInverseDistance (ViSession instrumentHandle,
                                                      ViInt32 cursor,
                                                      ViReal64* cursorDistance);
ViStatus _VI_FUNC rsscope_CursorSearch (ViSession instrumentHandle, ViInt32 cursor,
                                        ViInt32 search);
ViStatus _VI_FUNC rsscope_ConfigureCursorPeakExcursion (ViSession instrumentHandle,
                                                        ViInt32 cursor,
                                                        ViInt32 peakExcursion);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeMainMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeAdditionalMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViBoolean enabled);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeSettings (ViSession instrumentHandle,
                                                          ViInt32 measurement,
                                                          ViInt32 signalThreshold,
                                                          ViReal64 areaLevel,
                                                          ViInt32 pulseTrainCount);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeSlope (ViSession instrumentHandle,
                                                       ViInt32 measurement,
                                                       ViInt32 countType,
                                                       ViInt32 slope);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeAdvancedDelaySetup
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 sourceNumber,
              ViInt32 levelSelection, ViInt32 slope, ViInt32 direction,
              ViInt32 edgeNumber);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeReferenceLevel
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 type,
              ViInt32 referenceLevel);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeLimitCheck
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViInt32 limitCheck);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeLimitCheckLimits
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerLimit, ViReal64 upperLimit);
ViStatus _VI_FUNC rsscope_ConfigureAmplitudeTimeLimitCheckMargins
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerMargin, ViReal64 upperMargin);
ViStatus _VI_FUNC rsscope_ConfigureEnvelopeMeasurement (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViInt32 evnelope);
ViStatus _VI_FUNC rsscope_ConfigureEyeJitterMainMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction);
ViStatus _VI_FUNC rsscope_ConfigureEyeJitterAdditionalMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViBoolean enabled);
ViStatus _VI_FUNC rsscope_ConfigureEyeJitterLimitCheck (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViInt32 measurementType,
                                                        ViInt32 limitCheck);
ViStatus _VI_FUNC rsscope_ConfigureEyeJitterLimitCheckLimits
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerLimit, ViReal64 upperLimit);
ViStatus _VI_FUNC rsscope_ConfigureEyeJitterLimitCheckMargins
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerMargin, ViReal64 upperMargin);
ViStatus _VI_FUNC rsscope_ConfigureSpectrumMainMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction);
ViStatus _VI_FUNC rsscope_ConfigureSpectrumAdditionalMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViBoolean enabled);
ViStatus _VI_FUNC rsscope_ConfigureSpectrumSettings (ViSession instrumentHandle,
                                                     ViInt32 measurement,
                                                     ViInt32 nDBDown,
                                                     ViReal64 channelBandwidth,
                                                     ViReal64 channelCenterFrequency,
                                                     ViReal64 occupiedBandwidth,
                                                     ViInt32 noiseReject);
ViStatus _VI_FUNC rsscope_ConfigureSpectrumLimitCheck (ViSession instrumentHandle,
                                                       ViInt32 measurement,
                                                       ViInt32 measurementType,
                                                       ViInt32 limitCheck);
ViStatus _VI_FUNC rsscope_ConfigureSpectrumLimitCheckLimits
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerLimit, ViReal64 upperLimit);
ViStatus _VI_FUNC rsscope_ConfigureSpectrumLimitCheckMargins
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerMargin, ViReal64 upperMargin);
ViStatus _VI_FUNC rsscope_ConfigureHistogramMainMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction);
ViStatus _VI_FUNC rsscope_ConfigureHistogramAdditionalMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViBoolean enabled);
ViStatus _VI_FUNC rsscope_SelectHistogram (ViSession instrumentHandle,
                                           ViInt32 measurement,
                                           ViString measurementType);
ViStatus _VI_FUNC rsscope_ConfigureHistogramProbabilityDomainMarkerSettings
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 reference,
              ViInt32 delta);
ViStatus _VI_FUNC rsscope_ConfigureHistogramLimitCheck (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViInt32 measurementType,
                                                        ViInt32 limitCheck);
ViStatus _VI_FUNC rsscope_ConfigureHistogramLimitCheckLimits
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerLimit, ViReal64 upperLimit);
ViStatus _VI_FUNC rsscope_ConfigureHistogramLimitCheckMargins
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementType, ViReal64 lowerMargin, ViReal64 upperMargin);
ViStatus _VI_FUNC rsscope_ConfigureHistogramDisplay (ViSession instrumentHandle,
                                                     ViInt32 measurement,
                                                     ViBoolean displaySourceHistogram);
ViStatus _VI_FUNC rsscope_CreateNewHistogram (ViSession instrumentHandle,
                                              ViString histogramName,
                                              ViInt32 histogramSource,
                                              ViBoolean relativeValues,
                                              ViReal64 xStart, ViReal64 xStop,
                                              ViReal64 yStart, ViReal64 yStop);
ViStatus _VI_FUNC rsscope_ConfigureHistogramSource (ViSession instrumentHandle,
                                                    ViString histogramName,
                                                    ViInt32 histogramSource);
ViStatus _VI_FUNC rsscope_ResetHistogram (ViSession instrumentHandle,
                                          ViString histogramName);
ViStatus _VI_FUNC rsscope_RemoveHistogram (ViSession instrumentHandle,
                                           ViString histogramName);
ViStatus _VI_FUNC rsscope_ConfigureHistogramType (ViSession instrumentHandle,
                                                  ViString histogramName,
                                                  ViInt32 type);
ViStatus _VI_FUNC rsscope_ConfigureHistogramVertical (ViSession instrumentHandle,
                                                      ViString histogramName,
                                                      ViInt32 mode, ViReal64 start,
                                                      ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureHistogramHorizontal (ViSession instrumentHandle,
                                                        ViString histogramName,
                                                        ViInt32 mode,
                                                        ViReal64 start,
                                                        ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureGateState (ViSession instrumentHandle,
                                              ViInt32 measurement,
                                              ViBoolean useGate);
ViStatus _VI_FUNC rsscope_ConfigureGateShow (ViSession instrumentHandle,
                                             ViInt32 measurement,
                                             ViBoolean showGate);
ViStatus _VI_FUNC rsscope_ConfigureGateDefinitionZoom (ViSession instrumentHandle,
                                                       ViInt32 measurement,
                                                       ViBoolean zoomCoupling,
                                                       ViInt32 zoomDiagram);
ViStatus _VI_FUNC rsscope_ConfigureGateDefinitionStartStop
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 mode,
              ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureGateNoise (ViSession instrumentHandle,
                                              ViInt32 measurement,
                                              ViInt32 evaluationArea);
ViStatus _VI_FUNC rsscope_ConfigureLongTermState (ViSession instrumentHandle,
                                                  ViInt32 measurement,
                                                  ViBoolean longTermState);
ViStatus _VI_FUNC rsscope_ConfigureLongTermTotalMeasurementTime
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 totalMeasurementTime);
ViStatus _VI_FUNC rsscope_ConfigureLongTermMeasurementPoints
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementPoints);
ViStatus _VI_FUNC rsscope_ConfigureLongTermVerticalScaling
             (ViSession instrumentHandle, ViInt32 measurement,
              ViReal64 verticalScale, ViReal64 verticalOffset);
ViStatus _VI_FUNC rsscope_LongTermVerticalAutoScale (ViSession instrumentHandle,
                                                     ViInt32 measurement);
ViStatus _VI_FUNC rsscope_ConfigureStatisticsState (ViSession instrumentHandle,
                                                    ViInt32 measurement,
                                                    ViBoolean statistics);
ViStatus _VI_FUNC rsscope_ConfigureHistogramState (ViSession instrumentHandle,
                                                   ViInt32 measurement,
                                                   ViBoolean showHistogram);
ViStatus _VI_FUNC rsscope_ConfigureResetStatisticsSettings
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 resetStatisticsMode, ViReal64 resetTime, ViInt32 resetCount);
ViStatus _VI_FUNC rsscope_ResetStatistics (ViSession instrumentHandle,
                                           ViInt32 measurement);
ViStatus _VI_FUNC rsscope_ConfigureStatisticsAverageCount
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 statisticsAverageCount);
ViStatus _VI_FUNC rsscope_ConfigureEnvironmentSensorState
             (ViSession instrumentHandle, ViInt32 measurement, ViBoolean useSensor);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevel (ViSession instrumentHandle,
                                                   ViInt32 source,
                                                   ViInt32 referenceLevelMode,
                                                   ViInt32 levelDefinition,
                                                   ViInt32 userLevelSelection);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevelAutoSettings
             (ViSession instrumentHandle, ViInt32 source, ViInt32 signalLevelMode,
              ViBoolean histogramAveraging, ViInt32 averageCount);
ViStatus _VI_FUNC rsscope_ConfigureReferenceUserSignalLevel
             (ViSession instrumentHandle, ViInt32 source, ViReal64 topDistance,
              ViReal64 bottomDistance, ViReal64 highSignalLevel,
              ViReal64 lowSignalLevel);
ViStatus _VI_FUNC rsscope_ConfigureUserReferenceLevel (ViSession instrumentHandle,
                                                       ViInt32 source,
                                                       ViReal64 topDistance,
                                                       ViReal64 bottomDistance,
                                                       ViReal64 upperLevel,
                                                       ViReal64 lowerLevel);
ViStatus _VI_FUNC rsscope_ConfigureUserMiddleReferenceLevel
             (ViSession instrumentHandle, ViInt32 source, ViReal64 middleLevel);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevelRelativeLevels
             (ViSession instrumentHandle, ViInt32 source, ViInt32 relativeLevels);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevelRelativeUserLevels
             (ViSession instrumentHandle, ViInt32 source, ViInt32 upperLevel,
              ViInt32 middleLevel, ViInt32 lowerLevel);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevelHysteresis
             (ViSession instrumentHandle, ViInt32 source, ViReal64 hysteresis);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevelTube (ViSession instrumentHandle,
                                                       ViInt32 source,
                                                       ViReal64 topOuter,
                                                       ViReal64 topInner,
                                                       ViReal64 bottomInner,
                                                       ViReal64 bottomOuter);
ViStatus _VI_FUNC rsscope_ConfigureReferenceLevelTubeRelative
             (ViSession instrumentHandle, ViInt32 source, ViInt32 relativeOuter,
              ViInt32 relativeInner);
ViStatus _VI_FUNC rsscope_ActualRecordLength (ViSession instrumentHandle,
                                              ViInt32* actualRecordLength);
ViStatus _VI_FUNC rsscope_SampleMode (ViSession instrumentHandle,
                                      ViInt32* sampleMode);
ViStatus _VI_FUNC rsscope_SampleRate (ViSession instrumentHandle,
                                      ViReal64* sampleRate);
ViStatus _VI_FUNC rsscope_AutoProbeSenseValue (ViSession instrumentHandle,
                                               ViInt32 channel, ViInt32 bufferSize,
                                               ViChar _VI_FAR autoProbeSenseValue[]);
ViStatus _VI_FUNC rsscope_QueryMaskTestResults (ViSession instrumentHandle,
                                                ViString maskName,
                                                ViUInt32* acquisitionsCompleted,
                                                ViUInt32* acquisitionsRemaining,
                                                ViInt32* state,
                                                ViUInt32* sampleHits,
                                                ViUInt32* acquisitionHits,
                                                ViUInt32* failRate,
                                                ViInt32* testResult);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestActionsOnEvent
             (ViSession instrumentHandle, ViString maskName, ViInt32 event,
              ViInt32 action);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestDefinition (ViSession instrumentHandle,
                                                       ViInt32 action,
                                                       ViString maskName);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestEnable (ViSession instrumentHandle,
                                                   ViString maskName,
                                                   ViBoolean state);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestDefinitionType
             (ViSession instrumentHandle, ViString maskName,
              ViInt32 definitionType);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestSource (ViSession instrumentHandle,
                                                   ViString maskName,
                                                   ViInt32 maskSource);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestSettings (ViSession instrumentHandle,
                                                     ViString maskName,
                                                     ViInt32 failCondition,
                                                     ViUInt32 violationTolerance);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestSegments (ViSession instrumentHandle,
                                                     ViString maskName,
                                                     ViInt32 maskSegment,
                                                     ViBoolean state,
                                                     ViInt32 region);
ViStatus _VI_FUNC rsscope_QueryMaskTestSegmentsCount (ViSession instrumentHandle,
                                                      ViString maskName,
                                                      ViInt32 maskSegment,
                                                      ViInt32* segmentsNumber);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestSegmentsOperation
             (ViSession instrumentHandle, ViString maskName, ViInt32 maskSegment,
              ViInt32 action);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestSegmentDefinition
             (ViSession instrumentHandle, ViString maskName, ViInt32 maskSegment,
              ViInt32 pointIndex, ViReal64 xValue, ViReal64 yValue);
ViStatus _VI_FUNC rsscope_QueryMaskTestSegmentDefinitionCount
             (ViSession instrumentHandle, ViString maskName, ViInt32 maskSegment,
              ViInt32* pointsNumber);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestSegmentDefinitionOperation
             (ViSession instrumentHandle, ViString maskName,
              ViInt32 definitionOfSegment, ViInt32 pointIndex, ViInt32 action);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestRescale (ViSession instrumentHandle,
                                                    ViInt32 definitionOfSegment,
                                                    ViString maskName,
                                                    ViReal64 offsetX,
                                                    ViInt32 factorX,
                                                    ViReal64 offsetY,
                                                    ViInt32 factorY);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestWaveformCopy (ViSession instrumentHandle,
                                                         ViString maskName,
                                                         ViInt32 usedReference);
ViStatus _VI_FUNC rsscope_ConfigureMaskTestWaveformRescale
             (ViSession instrumentHandle, ViString maskName,
              ViReal64 horizontalWidth, ViReal64 verticalWidth,
              ViInt32 verticalStretch, ViReal64 verticalPosition);
ViStatus _VI_FUNC rsscope_MaskTestRecalculate (ViSession instrumentHandle,
                                               ViInt32 definitionOfSegment,
                                               ViString maskName);
ViStatus _VI_FUNC rsscope_NewSearch (ViSession instrumentHandle,
                                     ViString searchName);
ViStatus _VI_FUNC rsscope_DeleteSearch (ViSession instrumentHandle,
                                        ViString searchName);
ViStatus _VI_FUNC rsscope_ConfigureSearchSource (ViSession instrumentHandle,
                                                 ViString searchName,
                                                 ViInt32 searchConditionSource);
ViStatus _VI_FUNC rsscope_ConfigureSearchCategory (ViSession instrumentHandle,
                                                   ViString searchName,
                                                   ViInt32 searchCategory);
ViStatus _VI_FUNC rsscope_ConfigureSearchControl (ViSession instrumentHandle,
                                                  ViString searchName,
                                                  ViBoolean searchOnline);
ViStatus _VI_FUNC rsscope_PerformSearch (ViSession instrumentHandle,
                                         ViString searchName,
                                         ViInt32 searchResults);
ViStatus _VI_FUNC rsscope_ClearSearchResults (ViSession instrumentHandle,
                                              ViString searchName);
ViStatus _VI_FUNC rsscope_QuerySearchResults (ViSession instrumentHandle,
                                              ViString searchName,
                                              ViInt32 bufferSize,
                                              ViInt32 _VI_FAR acquisitionIndex[],
                                              ViReal64 _VI_FAR xPosition[],
                                              ViReal64 _VI_FAR yPosition[],
                                              ViInt32 _VI_FAR typeOfSearchResult[],
                                              ViInt32 _VI_FAR slope[],
                                              ViReal64 _VI_FAR timeResult[],
                                              ViInt32* actualValues);
ViStatus _VI_FUNC rsscope_SearchTriggerCopyConfiguration (ViSession instrumentHandle,
                                                          ViString searchName,
                                                          ViInt32 triggerType,
                                                          ViInt32 copyFrom);
ViStatus _VI_FUNC rsscope_ConfigureEdgeTriggerSearch (ViSession instrumentHandle,
                                                      ViString searchName,
                                                      ViBoolean triggerState,
                                                      ViInt32 searchSource,
                                                      ViReal64 triggerLevel,
                                                      ViInt32 triggerSlope);
ViStatus _VI_FUNC rsscope_ConfigureGlitchTriggerSearch (ViSession instrumentHandle,
                                                        ViString searchName,
                                                        ViBoolean triggerState,
                                                        ViInt32 searchSource,
                                                        ViReal64 triggerLevel,
                                                        ViReal64 glitchWidth,
                                                        ViInt32 glitchPolarity,
                                                        ViInt32 glitchCondition);
ViStatus _VI_FUNC rsscope_ConfigureWidthTriggerSearch (ViSession instrumentHandle,
                                                       ViString searchName,
                                                       ViBoolean triggerState,
                                                       ViInt32 searchSource,
                                                       ViReal64 triggerLevel,
                                                       ViReal64 width,
                                                       ViReal64 widthDelta,
                                                       ViInt32 widthPolarity,
                                                       ViInt32 widthRange);
ViStatus _VI_FUNC rsscope_ConfigureRuntTriggerSearch (ViSession instrumentHandle,
                                                      ViString searchName,
                                                      ViBoolean triggerState,
                                                      ViInt32 searchSource,
                                                      ViReal64 runtLowThreshold,
                                                      ViReal64 runtHighThreshold,
                                                      ViInt32 runtPolarity);
ViStatus _VI_FUNC rsscope_ConfigureRuntTriggerSearchRange
             (ViSession instrumentHandle, ViString searchName, ViReal64 runtWidth,
              ViReal64 runtDelta, ViInt32 runtRange);
ViStatus _VI_FUNC rsscope_ConfigureWindowTriggerSearch (ViSession instrumentHandle,
                                                        ViString searchName,
                                                        ViBoolean triggerState,
                                                        ViInt32 searchSource,
                                                        ViReal64 windowLowerLimit,
                                                        ViReal64 windowUpperLimit);
ViStatus _VI_FUNC rsscope_ConfigureWindowTriggerSearchRange
             (ViSession instrumentHandle, ViString searchName,
              ViInt32 verticalCondition, ViInt32 timeCondition,
              ViReal64 windowWidth, ViReal64 windowDelta);
ViStatus _VI_FUNC rsscope_ConfigureTimeoutTriggerSearch (ViSession instrumentHandle,
                                                         ViString searchName,
                                                         ViBoolean triggerState,
                                                         ViInt32 searchSource,
                                                         ViReal64 triggerLevel,
                                                         ViReal64 timeoutValue,
                                                         ViInt32 timeoutCondition);
ViStatus _VI_FUNC rsscope_ConfigureIntervalTriggerSearch (ViSession instrumentHandle,
                                                          ViString searchName,
                                                          ViBoolean triggerState,
                                                          ViInt32 searchSource,
                                                          ViReal64 triggerLevel,
                                                          ViReal64 intervalWidth,
                                                          ViReal64 intervalDelta,
                                                          ViInt32 intervalPolarity,
                                                          ViInt32 intervalCondition);
ViStatus _VI_FUNC rsscope_ConfigureSlewRateTriggerSearch (ViSession instrumentHandle,
                                                          ViString searchName,
                                                          ViBoolean triggerState,
                                                          ViInt32 searchSource,
                                                          ViReal64 slewRateLowerLimit,
                                                          ViReal64 slewRateUpperLimit);
ViStatus _VI_FUNC rsscope_ConfigureSlewRateTriggerSearchRange
             (ViSession instrumentHandle, ViString searchName, ViReal64 slewRate,
              ViReal64 slewRateDelta, ViInt32 slewRateCondition,
              ViInt32 slewRatePolarity);
ViStatus _VI_FUNC rsscope_ConfigureData2ClockTriggerSearch
             (ViSession instrumentHandle, ViString searchName,
              ViBoolean triggerState, ViInt32 searchSource, ViReal64 dataLevel,
              ViInt32 clockSource, ViReal64 clockLevel, ViReal64 holdTime,
              ViReal64 setupTime, ViInt32 clockEdge);
ViStatus _VI_FUNC rsscope_ConfigureStateTriggerSearch (ViSession instrumentHandle,
                                                       ViString searchName,
                                                       ViBoolean triggerState,
                                                       ViInt32 clockSource,
                                                       ViInt32 clockEdge,
                                                       ViReal64 clockLevel);
ViStatus _VI_FUNC rsscope_ConfigureStateTriggerSearchQualification
             (ViSession instrumentHandle, ViString searchName, ViInt32 channel,
              ViBoolean channelEnabled, ViInt32 channelLogic);
ViStatus 
    _VI_FUNC rsscope_ConfigureStateTriggerSearchQualificationMulitchannelLogic
        (ViSession instrumentHandle, ViString searchName,
         ViInt32 channelCombination, ViInt32 multichannelLogic);
ViStatus _VI_FUNC rsscope_ConfigurePatternTriggerSearch (ViSession instrumentHandle,
                                                         ViString searchName,
                                                         ViBoolean triggerState,
                                                         ViInt32 patternMode,
                                                         ViInt32 timeoutCondition,
                                                         ViReal64 timeout,
                                                         ViReal64 patternWidth,
                                                         ViReal64 patternDelta,
                                                         ViInt32 patternCondition);
ViStatus _VI_FUNC rsscope_ConfigurePatternTriggerSearchQualification
             (ViSession instrumentHandle, ViString searchName, ViInt32 channel,
              ViBoolean channelEnabled, ViInt32 channelLogic);
ViStatus 
    _VI_FUNC rsscope_ConfigurePatternTriggerSearchQualificationMulitchannelLogic
        (ViSession instrumentHandle, ViString searchName,
         ViInt32 channelCombination, ViInt32 multichannelLogic);
ViStatus _VI_FUNC rsscope_QueryTriggerSearchCondition (ViSession instrumentHandle,
                                                       ViString searchName,
                                                       ViInt32 bufferSize,
                                                       ViChar _VI_FAR searchLogic[]);
ViStatus _VI_FUNC rsscope_ConfigureSearchGateState (ViSession instrumentHandle,
                                                    ViString searchName,
                                                    ViBoolean useGate);
ViStatus _VI_FUNC rsscope_ConfigureSearchGateShow (ViSession instrumentHandle,
                                                   ViString searchName,
                                                   ViBoolean showGate);
ViStatus _VI_FUNC rsscope_ConfigureSearchGateDefinitionZoom
             (ViSession instrumentHandle, ViString searchName,
              ViBoolean zoomCoupling, ViInt32 zoomDiagram);
ViStatus _VI_FUNC rsscope_ConfigureSearchGateDefinitionStartStop
             (ViSession instrumentHandle, ViString searchName, ViInt32 mode,
              ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureSearchResultTable (ViSession instrumentHandle,
                                                      ViString searchName,
                                                      ViBoolean showResultTable,
                                                      ViInt32 sortMode,
                                                      ViBoolean sortAscending,
                                                      ViInt32 maxResultCount);
ViStatus _VI_FUNC rsscope_ConfigureSearchZoomWindowState (ViSession instrumentHandle,
                                                          ViString searchName,
                                                          ViBoolean showSearchZoomWindows);
ViStatus _VI_FUNC rsscope_ConfigureSearchZoomWindowXAxis (ViSession instrumentHandle,
                                                          ViString searchName,
                                                          ViInt32 horizonatalMode,
                                                          ViReal64 position,
                                                          ViReal64 range);
ViStatus _VI_FUNC rsscope_ConfigureSearchZoomWindowYAxis (ViSession instrumentHandle,
                                                          ViString searchName,
                                                          ViInt32 verticalMode,
                                                          ViReal64 position,
                                                          ViReal64 range);
ViStatus _VI_FUNC rsscope_ConfigureSearchNoiseReject (ViSession instrumentHandle,
                                                      ViString searchName,
                                                      ViInt32 searchConditionSource,
                                                      ViBoolean useNoiseReject,
                                                      ViInt32 hysteresisMode,
                                                      ViReal64 hysteresis);
ViStatus _VI_FUNC rsscope_ConfigureDecodeState (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViBoolean state);
ViStatus _VI_FUNC rsscope_ConfigureBusLabel (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViString busLabel);
ViStatus _VI_FUNC rsscope_ShowDecodeTable (ViSession instrumentHandle,
                                           ViInt32 serialBus, ViBoolean showTable);
ViStatus _VI_FUNC rsscope_ConfigureLabelList (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViBoolean state);
ViStatus _VI_FUNC rsscope_ConfigureI2CSource (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 line,
                                              ViInt32 waveformSource);
ViStatus _VI_FUNC rsscope_ConfigureI2CThreshold (ViSession instrumentHandle,
                                                 ViInt32 serialBus, ViInt32 preset,
                                                 ViReal64 SCLThreshold,
                                                 ViReal64 SDAThreshold);
ViStatus _VI_FUNC rsscope_ConfigureI2CRWBit (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 RWBit);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerType (ViSession instrumentHandle,
                                                   ViInt32 trigger, ViInt32 type);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerAddress (ViSession instrumentHandle,
                                                      ViInt32 trigger,
                                                      ViInt32 addressType,
                                                      ViInt32 RWBitAddress,
                                                      ViInt32 condition,
                                                      ViString addressMin,
                                                      ViString addressMax);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerAddressORState
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 ORSlot,
              ViBoolean ORSlotState);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerAddressOR (ViSession instrumentHandle,
                                                        ViInt32 trigger,
                                                        ViInt32 ORSlot,
                                                        ViInt32 addressType,
                                                        ViInt32 RWBitAddress,
                                                        ViString address);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerData (ViSession instrumentHandle,
                                                   ViInt32 trigger,
                                                   ViInt32 condition,
                                                   ViString addressMin,
                                                   ViString addressMax);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerDataPosition
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 condition,
              ViInt32 indexMin, ViInt32 indexMax);
ViStatus _VI_FUNC rsscope_ConfigureI2CTriggerNoAck (ViSession instrumentHandle,
                                                    ViInt32 trigger,
                                                    ViBoolean addressNack,
                                                    ViBoolean dataWriteNack,
                                                    ViBoolean dataReadNack);
ViStatus _VI_FUNC rsscope_QueryI2CFrameCount (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryI2CFrameStatus (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 frame,
                                               ViInt32* status,
                                               ViReal64* frameStart,
                                               ViReal64* frameStop,
                                               ViInt32* addresType,
                                               ViInt32* address, ViInt32* RWBit,
                                               ViInt32* ackBit);
ViStatus _VI_FUNC rsscope_QueryI2CFrameAccessBitStart (ViSession instrumentHandle,
                                                       ViInt32 serialBus,
                                                       ViInt32 frame,
                                                       ViReal64* accessBitStart);
ViStatus _VI_FUNC rsscope_QueryI2CFrameSlaveAddress (ViSession instrumentHandle,
                                                     ViInt32 serialBus,
                                                     ViInt32 frame,
                                                     ViInt32* address);
ViStatus _VI_FUNC rsscope_QueryI2CFrameAddressAckBitStartTime
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32 frame,
              ViReal64* addressStart);
ViStatus _VI_FUNC rsscope_QueryI2CFrameAddressAckBitStart
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32 frame,
              ViReal64* ackBitStart);
ViStatus _VI_FUNC rsscope_QueryI2CFrameAddressComplete (ViSession instrumentHandle,
                                                        ViInt32 serialBus,
                                                        ViInt32 frame,
                                                        ViBoolean* complete);
ViStatus _VI_FUNC rsscope_QueryI2CFrameLength (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 frame,
                                               ViInt32* length);
ViStatus _VI_FUNC rsscope_QueryI2CFrameData (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 frame,
                                             ViInt32 byteNumber, ViInt32* data,
                                             ViInt32* ackBit);
ViStatus _VI_FUNC rsscope_QueryI2CFrameDataByteStart (ViSession instrumentHandle,
                                                      ViInt32 serialBus,
                                                      ViInt32 frame,
                                                      ViInt32 byteNumber,
                                                      ViReal64* startTime);
ViStatus _VI_FUNC rsscope_QueryI2CFrameDataComplete (ViSession instrumentHandle,
                                                     ViInt32 serialBus,
                                                     ViInt32 frame,
                                                     ViInt32 byteNumber,
                                                     ViBoolean* complete);
ViStatus _VI_FUNC rsscope_QueryI2CFrameAllData (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32 frame,
                                                ViInt32 arraySize,
                                                ViInt32 _VI_FAR data[],
                                                ViInt32* returnedValues);
ViStatus _VI_FUNC rsscope_QueryI2CFrameLabel (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR label[]);
ViStatus _VI_FUNC rsscope_ConfigureSPISource (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 line,
                                              ViInt32 waveformSource);
ViStatus _VI_FUNC rsscope_ConfigureSPIThreshold (ViSession instrumentHandle,
                                                 ViInt32 serialBus, ViInt32 preset,
                                                 ViReal64 clockThreshold,
                                                 ViReal64 SSThreshold,
                                                 ViReal64 MISOThreshold,
                                                 ViReal64 MOSIThreshold);
ViStatus _VI_FUNC rsscope_ConfigureSPIPolarity (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32 line,
                                                ViInt32 polarity);
ViStatus _VI_FUNC rsscope_ConfigureSPIWord (ViSession instrumentHandle,
                                            ViInt32 serialBus, ViInt32 bitOrder,
                                            ViInt32 wordLength);
ViStatus _VI_FUNC rsscope_ConfigureSPIFrameStart (ViSession instrumentHandle,
                                                  ViInt32 serialBus,
                                                  ViInt32 frameCondition,
                                                  ViReal64 clockTimeout);
ViStatus _VI_FUNC rsscope_ConfigureSPITriggerType (ViSession instrumentHandle,
                                                   ViInt32 type);
ViStatus _VI_FUNC rsscope_ConfigureSPITriggerData (ViSession instrumentHandle,
                                                   ViInt32 trigger,
                                                   ViInt32 condition,
                                                   ViString MOSIPattern,
                                                   ViString MISOPattern);
ViStatus _VI_FUNC rsscope_ConfigureSPITriggerDataPosition
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 condition,
              ViInt32 searchMode, ViInt32 indexMin, ViInt32 indexMax);
ViStatus _VI_FUNC rsscope_QuerySPIFrameCount (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32* count);
ViStatus _VI_FUNC rsscope_QuerySPIWordCount (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 frame,
                                             ViInt32* count);
ViStatus _VI_FUNC rsscope_QuerySPIFrameStatus (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 frame,
                                               ViReal64* frameStart,
                                               ViReal64* frameStop,
                                               ViInt32* status);
ViStatus _VI_FUNC rsscope_QuerySPIFrameData (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 frame,
                                             ViInt32 word, ViReal64* valueStart,
                                             ViReal64* valueStop,
                                             ViInt32* MOSIValue,
                                             ViInt32* MISOValue);
ViStatus _VI_FUNC rsscope_QuerySPIFrameAllData (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32 frame,
                                                ViInt32 arraySize,
                                                ViInt32 _VI_FAR data[],
                                                ViInt32* returnedValues);
ViStatus _VI_FUNC rsscope_ConfigureUARTSource (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 line,
                                               ViInt32 waveformSource);
ViStatus _VI_FUNC rsscope_ConfigureUARTThreshold (ViSession instrumentHandle,
                                                  ViInt32 serialBus, ViInt32 preset,
                                                  ViReal64 rxThreshold,
                                                  ViReal64 txThreshold);
ViStatus _VI_FUNC rsscope_ConfigureUART (ViSession instrumentHandle,
                                         ViInt32 serialBus, ViInt32 bitRate,
                                         ViInt32 stopBits, ViInt32 dataBits,
                                         ViInt32 parity, ViInt32 polarity);
ViStatus _VI_FUNC rsscope_ConfigureUARTPackets (ViSession instrumentHandle,
                                                ViInt32 packets, ViString endWord,
                                                ViReal64 packetsTimeout);
ViStatus _VI_FUNC rsscope_ConfigureUARTTriggerType (ViSession instrumentHandle,
                                                    ViInt32 trigger, ViInt32 type,
                                                    ViInt32 source);
ViStatus _VI_FUNC rsscope_ConfigureUARTTriggerData (ViSession instrumentHandle,
                                                    ViInt32 trigger,
                                                    ViInt32 condition,
                                                    ViString pattern,
                                                    ViInt32 position,
                                                    ViInt32 indexMin,
                                                    ViInt32 indexMax);
ViStatus _VI_FUNC rsscope_QueryUARTFrameCount (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryUARTFrameData (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 word,
                                              ViInt32* source, ViInt32* status,
                                              ViReal64* start, ViInt32* txValue,
                                              ViInt32* rxValue);
ViStatus _VI_FUNC rsscope_ConfigureLINSource (ViSession instrumentHandle,
                                              ViInt32 serialBus,
                                              ViInt32 waveformSource);
ViStatus _VI_FUNC rsscope_ConfigureLINThreshold (ViSession instrumentHandle,
                                                 ViInt32 serialBus, ViInt32 preset,
                                                 ViReal64 manualThreshold);
ViStatus _VI_FUNC rsscope_ConfigureLINPolarity (ViSession instrumentHandle,
                                                ViInt32 serialBus,
                                                ViInt32 polarity);
ViStatus _VI_FUNC rsscope_ConfigureLINStandard (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32 standard,
                                                ViInt32 bitRate);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerType (ViSession instrumentHandle,
                                                   ViInt32 trigger, ViInt32 type);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerID (ViSession instrumentHandle,
                                                 ViInt32 trigger, ViInt32 condition,
                                                 ViString IDMin, ViString IDMax);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerIDOR (ViSession instrumentHandle,
                                                   ViInt32 trigger, ViInt32 ORSlot,
                                                   ViBoolean ORSlotState,
                                                   ViString frameID);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerData (ViSession instrumentHandle,
                                                   ViInt32 trigger,
                                                   ViInt32 condition,
                                                   ViString dataMin,
                                                   ViString dataMax);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerDataSetup (ViSession instrumentHandle,
                                                        ViInt32 trigger,
                                                        ViInt32 condition,
                                                        ViInt32 dataLength,
                                                        ViInt32 transfer);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerErrorConditions
             (ViSession instrumentHandle, ViInt32 trigger, ViBoolean checksum,
              ViBoolean IDParityError, ViBoolean syncError);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerCRCErrorPattern
             (ViSession instrumentHandle, ViInt32 trigger, ViString frameID,
              ViInt32 dataLength);
ViStatus _VI_FUNC rsscope_ConfigureLINTriggerCRCErrorStandard
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 standard);
ViStatus _VI_FUNC rsscope_QueryLINFrameCount (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryLINFrameStatus (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 frame,
                                               ViInt32* frameStatus,
                                               ViReal64* frameStart,
                                               ViReal64* frameStop,
                                               ViInt32* version);
ViStatus _VI_FUNC rsscope_QueryLINFrameID (ViSession instrumentHandle,
                                           ViInt32 serialBus, ViInt32 frame,
                                           ViInt32* value, ViInt32* parity,
                                           ViInt32* status);
ViStatus _VI_FUNC rsscope_QueryLINFrameField (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 field, ViInt32* fieldValue,
                                              ViInt32* fieldStatus);
ViStatus _VI_FUNC rsscope_QueryLINFrameData (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 frame,
                                             ViInt32 byteNumber, ViInt32* data,
                                             ViInt32* statusCode);
ViStatus _VI_FUNC rsscope_QueryLINFrameAllData (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32 frame,
                                                ViInt32 arraySize,
                                                ViInt32 _VI_FAR data[],
                                                ViInt32* returnedValues);
ViStatus _VI_FUNC rsscope_QueryLINFrameLabel (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR label[]);
ViStatus _VI_FUNC rsscope_ConfigureCANSource (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 line,
                                              ViInt32 waveformSource);
ViStatus _VI_FUNC rsscope_ConfigureCANThreshold (ViSession instrumentHandle,
                                                 ViInt32 serialBus, ViInt32 preset,
                                                 ViReal64 manualThreshold);
ViStatus _VI_FUNC rsscope_ConfigureCANBitRate (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 bitRate);
ViStatus _VI_FUNC rsscope_ConfigureCANJumpWidth (ViSession instrumentHandle,
                                                 ViInt32 serialBus,
                                                 ViReal64 jumpWidth);
ViStatus _VI_FUNC rsscope_ConfigureCANSamplePointAbsolute
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32 timeSegment1,
              ViInt32 timeSegment2);
ViStatus _VI_FUNC rsscope_ConfigureCANSamplePointRelative
             (ViSession instrumentHandle, ViInt32 serialBus, ViReal64 samplePoint);
ViStatus _VI_FUNC rsscope_ConfigureCANTriggerType (ViSession instrumentHandle,
                                                   ViInt32 trigger, ViInt32 type,
                                                   ViInt32 frameType);
ViStatus _VI_FUNC rsscope_ConfigureCANTriggerID (ViSession instrumentHandle,
                                                 ViInt32 trigger, ViInt32 IDType,
                                                 ViInt32 condition, ViString IDMin,
                                                 ViString IDMax);
ViStatus _VI_FUNC rsscope_ConfigureCANTriggerData (ViSession instrumentHandle,
                                                   ViInt32 trigger,
                                                   ViInt32 transfer,
                                                   ViInt32 condition,
                                                   ViString dataMin,
                                                   ViString dataMax);
ViStatus _VI_FUNC rsscope_ConfigureCANTriggerErrorConditions
             (ViSession instrumentHandle, ViInt32 trigger, ViBoolean CRC,
              ViBoolean stuffing, ViBoolean form, ViBoolean ack);
ViStatus _VI_FUNC rsscope_QueryCANFrameCount (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryCANFrameStatus (ViSession instrumentHandle,
                                               ViInt32 serialBus, ViInt32 frame,
                                               ViInt32* frameStatus,
                                               ViReal64* frameStart,
                                               ViReal64* frameStop,
                                               ViInt32* frameType);
ViStatus _VI_FUNC rsscope_QueryCANFrameID (ViSession instrumentHandle,
                                           ViInt32 serialBus, ViInt32 frame,
                                           ViInt32* IDType, ViInt32* IDValue,
                                           ViInt32* statusCode);
ViStatus _VI_FUNC rsscope_QueryCANFrameField (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 field, ViInt32* fieldValue,
                                              ViInt32* fieldStatus);
ViStatus _VI_FUNC rsscope_QueryCANFrameBitStuffingError (ViSession instrumentHandle,
                                                         ViInt32 serialBus,
                                                         ViInt32 frame,
                                                         ViReal64* errorPosition);
ViStatus _VI_FUNC rsscope_QueryCANFrameData (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 frame,
                                             ViInt32 byteNumber, ViInt32* data,
                                             ViInt32* statusCode);
ViStatus _VI_FUNC rsscope_QueryCANFrameAllData (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32 frame,
                                                ViInt32 arraySize,
                                                ViInt32 _VI_FAR data[],
                                                ViInt32* returnedValues);
ViStatus _VI_FUNC rsscope_QueryCANFrameLabel (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR label[]);
ViStatus _VI_FUNC rsscope_ConfigureFlexRaySource (ViSession instrumentHandle,
                                                  ViInt32 serialBus, ViInt32 line,
                                                  ViInt32 waveformSource,
                                                  ViInt32 channel,
                                                  ViBoolean separateHeaderBits,
                                                  ViInt32 bitRate);
ViStatus _VI_FUNC rsscope_ConfigureFlexRaySourceType (ViSession instrumentHandle,
                                                      ViInt32 serialBus,
                                                      ViInt32 sourceType);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayThresholdSingle
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32 polarity,
              ViInt32 preset, ViReal64 manualThresholdHigh,
              ViReal64 manualThresholdLow);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayThresholdDifferential
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32 preset,
              ViReal64 manualThresholdHigh, ViReal64 manualThresholdLow);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayThresholdLogic (ViSession instrumentHandle,
                                                          ViInt32 serialBus,
                                                          ViInt32 preset,
                                                          ViReal64 manualThresholdDataLine,
                                                          ViReal64 manualThresholdEnableLine);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerType (ViSession instrumentHandle,
                                                       ViInt32 trigger,
                                                       ViInt32 type);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerIndicatorBits
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 payloadPreamble,
              ViInt32 nullFrame, ViInt32 syncFrame, ViInt32 startupFrame);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerFrameID (ViSession instrumentHandle,
                                                          ViInt32 trigger,
                                                          ViInt32 condition,
                                                          ViString IDMin,
                                                          ViString IDMax);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerPayloadLength
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 condition,
              ViInt32 payloadMin, ViInt32 payloadMax);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerCycleCount
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 condition,
              ViInt32 cycleMin, ViInt32 cycleMax, ViInt32 cycleStep);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerData (ViSession instrumentHandle,
                                                       ViInt32 trigger,
                                                       ViInt32 condition,
                                                       ViString dataMin,
                                                       ViString dataMax);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerDataPosition
             (ViSession instrumentHandle, ViInt32 trigger, ViInt32 condition,
              ViInt32 positionMin, ViInt32 positionMax);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerSymbol (ViSession instrumentHandle,
                                                         ViInt32 trigger,
                                                         ViInt32 symbol);
ViStatus _VI_FUNC rsscope_ConfigureFlexRayTriggerErrorConditions
             (ViSession instrumentHandle, ViInt32 trigger, ViBoolean FSS,
              ViBoolean BSS, ViBoolean FES, ViBoolean headerCRC,
              ViBoolean payloadCRC);
ViStatus _VI_FUNC rsscope_QueryFlexRayFrameCount (ViSession instrumentHandle,
                                                  ViInt32 serialBus,
                                                  ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryFlexRayCycleCount (ViSession instrumentHandle,
                                                  ViInt32 serialBus, ViInt32 frame,
                                                  ViInt32* count);
ViStatus _VI_FUNC rsscope_QueryFlexRayFrameStatus (ViSession instrumentHandle,
                                                   ViInt32 serialBus, ViInt32 frame,
                                                   ViInt32* frameStatus,
                                                   ViReal64* frameStart,
                                                   ViReal64* frameStop,
                                                   ViInt32* frameType);
ViStatus _VI_FUNC rsscope_QueryFlexRayFrameField (ViSession instrumentHandle,
                                                  ViInt32 serialBus, ViInt32 frame,
                                                  ViInt32 field,
                                                  ViInt32* fieldValue,
                                                  ViInt32* fieldStatus);
ViStatus _VI_FUNC rsscope_QueryFlexRayFrameAllData (ViSession instrumentHandle,
                                                    ViInt32 serialBus,
                                                    ViInt32 frame,
                                                    ViInt32 arraySize,
                                                    ViInt32 _VI_FAR data[],
                                                    ViInt32* returnedValues);
ViStatus _VI_FUNC rsscope_QueryFlexRayFrameLabel (ViSession instrumentHandle,
                                                  ViInt32 serialBus, ViInt32 frame,
                                                  ViInt32 bufferSize,
                                                  ViChar _VI_FAR label[]);
ViStatus _VI_FUNC rsscope_HardcopySetFileName (ViSession instrumentHandle,
                                               ViString name);
ViStatus _VI_FUNC rsscope_ConfigureHardcopyDevice (ViSession instrumentHandle,
                                                   ViInt32 device,
                                                   ViInt32 destination,
                                                   ViBoolean color,
                                                   ViInt32 pageOrientation);
ViStatus _VI_FUNC rsscope_HardcopyPrint (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_HardcopyGetPrinterList (ViSession instrumentHandle,
                                                  ViInt32 bufferSize,
                                                  ViChar _VI_FAR printerList[]);
ViStatus _VI_FUNC rsscope_HardcopySetPrinter (ViSession instrumentHandle,
                                              ViInt32 device, ViString printerName);
ViStatus _VI_FUNC rsscope_FirmwareShutdown (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureComputerName (ViSession instrumentHandle,
                                                 ViString computerName);
ViStatus _VI_FUNC rsscope_QueryInstrumentInformation (ViSession instrumentHandle,
                                                      ViInt32 bufferSize,
                                                      ViChar _VI_FAR firmwaveVersion[],
                                                      ViChar _VI_FAR materialNumber[],
                                                      ViChar _VI_FAR serialNumber[]);
ViStatus _VI_FUNC rsscope_StartSelftest (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_SelftestStatus (ViSession instrumentHandle,
                                          ViInt32* selftestStatus);
ViStatus _VI_FUNC rsscope_SetAttributeViInt32 (ViSession instrumentHandle,
                                               ViChar _VI_FAR channelName[],
                                               ViAttr attributeID,
                                               ViInt32 attributeValue);
ViStatus _VI_FUNC rsscope_SetAttributeViReal64 (ViSession instrumentHandle,
                                                ViChar _VI_FAR channelName[],
                                                ViAttr attributeID,
                                                ViReal64 attributeValue);
ViStatus _VI_FUNC rsscope_SetAttributeViString (ViSession instrumentHandle,
                                                ViChar _VI_FAR channelName[],
                                                ViAttr attributeID,
                                                ViChar _VI_FAR attributeValue[]);
ViStatus _VI_FUNC rsscope_SetAttributeViBoolean (ViSession instrumentHandle,
                                                 ViChar _VI_FAR channelName[],
                                                 ViAttr attributeID,
                                                 ViBoolean attributeValue);
ViStatus _VI_FUNC rsscope_SetAttributeViSession (ViSession instrumentHandle,
                                                 ViChar _VI_FAR channelName[],
                                                 ViAttr attributeID,
                                                 ViSession attributeValue);
ViStatus _VI_FUNC rsscope_GetAttributeViInt32 (ViSession instrumentHandle,
                                               ViChar _VI_FAR channelName[],
                                               ViAttr attributeID,
                                               ViInt32* attributeValue);
ViStatus _VI_FUNC rsscope_GetAttributeViReal64 (ViSession instrumentHandle,
                                                ViChar _VI_FAR channelName[],
                                                ViAttr attributeID,
                                                ViReal64* attributeValue);
ViStatus _VI_FUNC rsscope_GetAttributeViString (ViSession instrumentHandle,
                                                ViChar _VI_FAR channelName[],
                                                ViAttr attributeID,
                                                ViInt32 bufferSize,
                                                ViChar _VI_FAR attributeValue[]);
ViStatus _VI_FUNC rsscope_GetAttributeViBoolean (ViSession instrumentHandle,
                                                 ViChar _VI_FAR channelName[],
                                                 ViAttr attributeID,
                                                 ViBoolean* attributeValue);
ViStatus _VI_FUNC rsscope_GetAttributeViSession (ViSession instrumentHandle,
                                                 ViChar _VI_FAR channelName[],
                                                 ViAttr attributeID,
                                                 ViSession* attributeValue);
ViStatus _VI_FUNC rsscope_CheckAttributeViInt32 (ViSession instrumentHandle,
                                                 ViChar _VI_FAR channelName[],
                                                 ViAttr attributeID,
                                                 ViInt32 attributeValue);
ViStatus _VI_FUNC rsscope_CheckAttributeViReal64 (ViSession instrumentHandle,
                                                  ViChar _VI_FAR channelName[],
                                                  ViAttr attributeID,
                                                  ViReal64 attributeValue);
ViStatus _VI_FUNC rsscope_CheckAttributeViString (ViSession instrumentHandle,
                                                  ViChar _VI_FAR channelName[],
                                                  ViAttr attributeID,
                                                  ViChar _VI_FAR attributeValue[]);
ViStatus _VI_FUNC rsscope_CheckAttributeViBoolean (ViSession instrumentHandle,
                                                   ViChar _VI_FAR channelName[],
                                                   ViAttr attributeID,
                                                   ViBoolean attributeValue);
ViStatus _VI_FUNC rsscope_CheckAttributeViSession (ViSession instrumentHandle,
                                                   ViChar _VI_FAR channelName[],
                                                   ViAttr attributeID,
                                                   ViSession attributeValue);
ViStatus _VI_FUNC rsscope_GetAttributeRepeatedCapabilityIds
             (ViSession instrumentHandle, ViUInt32 attributeID, ViInt32 bufferSize,
              ViChar _VI_FAR repeatedCapabilityId_s[]);
ViStatus _VI_FUNC rsscope_GetAttributeRepeatedCapabilityIdNames
             (ViSession instrumentHandle, ViUInt32 attributeID,
              ViString repeatedCapabilityId, ViInt32 bufferSize,
              ViChar _VI_FAR repeatedCapabilityIdName_s[]);
ViStatus _VI_FUNC rsscope_ConfigureMathEnabled (ViSession instrumentHandle,
                                                ViInt32 mathNumber,
                                                ViBoolean mathEnabled);
ViStatus _VI_FUNC rsscope_ConfigureMathSetup (ViSession instrumentHandle,
                                              ViInt32 mathNumber,
                                              ViInt32 calculationMethod,
                                              ViString expression);
ViStatus _VI_FUNC rsscope_ConfigureMathVerticalRange (ViSession instrumentHandle,
                                                      ViInt32 mathNumber,
                                                      ViReal64 verticalRange);
ViStatus _VI_FUNC rsscope_ConfigureMathVerticalScale (ViSession instrumentHandle,
                                                      ViInt32 mathNumber,
                                                      ViReal64 verticalScale);
ViStatus _VI_FUNC rsscope_ConfigureMathVerticalOffset (ViSession instrumentHandle,
                                                       ViInt32 mathNumber,
                                                       ViReal64 verticalOffset);
ViStatus _VI_FUNC rsscope_MathReset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureMathResetMode (ViSession instrumentHandle,
                                                  ViInt32 resetMode,
                                                  ViReal64 envelopeTimeout,
                                                  ViInt32 acquiredWaveforms);
ViStatus _VI_FUNC rsscope_ConfigureFFTFrequencyCenterSpan
             (ViSession instrumentHandle, ViInt32 mathNumber,
              ViReal64 centerFrequency, ViReal64 frequencySpan);
ViStatus _VI_FUNC rsscope_ConfigureFFTFrequencySpanFull (ViSession instrumentHandle,
                                                         ViInt32 mathNumber);
ViStatus _VI_FUNC rsscope_ConfigureFFTFrequencyStartStop (ViSession instrumentHandle,
                                                          ViInt32 mathNumber,
                                                          ViReal64 startFrequency,
                                                          ViReal64 stopFrequency);
ViStatus _VI_FUNC rsscope_ConfigureFFTResolutionBandwidth
             (ViSession instrumentHandle, ViInt32 mathNumber,
              ViBoolean RBWAndSpanCouplingEnabled, ViInt32 RBWRatio,
              ViReal64 resolutionBandwidth);
ViStatus _VI_FUNC rsscope_QueryFFTAdjustedResolutionBandwidth
             (ViSession instrumentHandle, ViInt32 mathNumber,
              ViReal64* adjustedRBW);
ViStatus _VI_FUNC rsscope_ConfigureFFTWindowType (ViSession instrumentHandle,
                                                  ViInt32 mathNumber,
                                                  ViInt32 windowType);
ViStatus _VI_FUNC rsscope_ConfigureFFTFrameSetup (ViSession instrumentHandle,
                                                  ViInt32 mathNumber,
                                                  ViInt32 arithmetic,
                                                  ViInt32 overlapFactor,
                                                  ViInt32 maxFrameCount);
ViStatus _VI_FUNC rsscope_QueryFFTFrameCoverage (ViSession instrumentHandle,
                                                 ViInt32 mathNumber,
                                                 ViInt32* frameCoverage);
ViStatus _VI_FUNC rsscope_ConfigureFFTMagnitude (ViSession instrumentHandle,
                                                 ViInt32 mathNumber,
                                                 ViInt32 magnitudeUnit,
                                                 ViReal64 referenceLevel,
                                                 ViInt32 magnitudeRange);
ViStatus _VI_FUNC rsscope_ConfigureFFTPhase (ViSession instrumentHandle,
                                             ViInt32 mathNumber, ViInt32 phaseUnit,
                                             ViBoolean phaseUnwrapEnabled,
                                             ViBoolean suppressionEnabled,
                                             ViReal64 suppressionThreshold);
ViStatus _VI_FUNC rsscope_ConfigureFFTGateState (ViSession instrumentHandle,
                                                 ViInt32 mathNumber,
                                                 ViBoolean useGate);
ViStatus _VI_FUNC rsscope_ConfigureFFTGateShow (ViSession instrumentHandle,
                                                ViInt32 mathNumber,
                                                ViBoolean showGate);
ViStatus _VI_FUNC rsscope_ConfigureFFTGateDefinitionZoom (ViSession instrumentHandle,
                                                          ViInt32 mathNumber,
                                                          ViBoolean zoomCoupling,
                                                          ViInt32 zoomDiagram);
ViStatus _VI_FUNC rsscope_ConfigureFFTGateDefinitionStartStop
             (ViSession instrumentHandle, ViInt32 mathNumber, ViInt32 mode,
              ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureFFTGateRecordLengthRBWCoupling
             (ViSession instrumentHandle, ViInt32 mathNumber, ViInt32 coupling);
ViStatus _VI_FUNC rsscope_QueryFFTGateRequiredAcquisitionTime
             (ViSession instrumentHandle, ViReal64* requiredAcquisitionTime);
ViStatus _VI_FUNC rsscope_ConfigureReferenceWaveformSource
             (ViSession instrumentHandle, ViInt32 referenceNumber, ViInt32 source);
ViStatus _VI_FUNC rsscope_UpdateReferenceWaveformWithSelectedSource
             (ViSession instrumentHandle, ViInt32 referenceNumber);
ViStatus _VI_FUNC rsscope_ConfigureReferenceWaveformDisplayState
             (ViSession instrumentHandle, ViInt32 referenceNumber,
              ViBoolean displayEnabled);
ViStatus _VI_FUNC rsscope_ClearReferenceWaveform (ViSession instrumentHandle,
                                                  ViInt32 referenceNumber);
ViStatus _VI_FUNC rsscope_ReferenceWaveformFileOperations
             (ViSession instrumentHandle, ViInt32 referenceNumber,
              ViString waveformName, ViInt32 operation);
ViStatus _VI_FUNC rsscope_ConfigureReferenceWaveformVerticalScaling
             (ViSession instrumentHandle, ViInt32 referenceNumber,
              ViInt32 verticalCoupling, ViReal64 verticalScale,
              ViReal64 verticalPosition);
ViStatus _VI_FUNC rsscope_ReferenceWaveformVerticalScalingSetToOriginal
             (ViSession instrumentHandle, ViInt32 referenceNumber);
ViStatus _VI_FUNC rsscope_ConfigureReferenceWaveformVerticalStretching
             (ViSession instrumentHandle, ViInt32 referenceNumber,
              ViBoolean verticalStretchingEnabled, ViReal64 factor,
              ViReal64 offset);
ViStatus _VI_FUNC rsscope_ConfigureReferenceWaveformHorizontalScaling
             (ViSession instrumentHandle, ViInt32 referenceNumber,
              ViInt32 horizontalCoupling);
ViStatus _VI_FUNC rsscope_ConfigureReferenceWaveformHorizontalStretching
             (ViSession instrumentHandle, ViInt32 referenceNumber,
              ViBoolean horizontalStretchingEnabled, ViReal64 factor,
              ViReal64 offset);
ViStatus _VI_FUNC rsscope_ReadWaveform (ViSession instrumentHandle, ViInt32 channel,
                                        ViInt32 waveform, ViInt32 waveformSize,
                                        ViInt32 maximumTime,
                                        ViReal64 _VI_FAR waveformArray[],
                                        ViInt32* actualPoints, ViReal64* initialX,
                                        ViReal64* xIncrement);
ViStatus _VI_FUNC rsscope_ReadMainWaveformMeasurement (ViSession instrumentHandle,
                                                       ViInt32 measurement,
                                                       ViInt32 statisticType,
                                                       ViInt32 maximumTime,
                                                       ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_ReadAmplitudeTimeWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViInt32 maximumTime, ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_ReadEyeJitterWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViInt32 maximumTime, ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_ReadHistogramWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViInt32 maximumTime, ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_ReadSpectrumWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViInt32 maximumTime, ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_ReadReferenceLevelResult (ViSession instrumentHandle,
                                                    ViInt32 measurement,
                                                    ViInt32 levelType,
                                                    ViReal64* referenceLevelResult);
ViStatus _VI_FUNC rsscope_InitiateAcquisition (ViSession instrumentHandle,
                                               ViInt32 action);
ViStatus _VI_FUNC rsscope_SendSoftwareTrigger (ViSession instrumentHandle,
                                               ViInt32 maximumTime);
ViStatus _VI_FUNC rsscope_FetchWaveform (ViSession instrumentHandle,
                                         ViInt32 channel, ViInt32 waveform,
                                         ViInt32 waveformSize,
                                         ViReal64 _VI_FAR waveformArray[],
                                         ViInt32* actualPoints, ViReal64* initialX,
                                         ViReal64* xIncrement);
ViStatus _VI_FUNC rsscope_FetchWaveformHeader (ViSession instrumentHandle,
                                               ViInt32 channel, ViInt32 waveform,
                                               ViInt32 bufferSize,
                                               ViChar _VI_FAR waveformHeader[]);
ViStatus _VI_FUNC rsscope_FetchMathWaveform (ViSession instrumentHandle,
                                             ViInt32 mathNumber,
                                             ViInt32 waveformSize,
                                             ViReal64 _VI_FAR waveformArray[],
                                             ViInt32* actualPoints);
ViStatus _VI_FUNC rsscope_FetchMathWaveformHeader (ViSession instrumentHandle,
                                                   ViInt32 mathNumber,
                                                   ViInt32 bufferSize,
                                                   ViChar _VI_FAR mathWaveformHeader[]);
ViStatus _VI_FUNC rsscope_FetchReferenceWaveform (ViSession instrumentHandle,
                                                  ViInt32 waveformSize,
                                                  ViReal64 _VI_FAR waveformArray[],
                                                  ViInt32* actualPoints);
ViStatus _VI_FUNC rsscope_FetchReferenceWaveformHeader (ViSession instrumentHandle,
                                                        ViInt32 bufferSize,
                                                        ViChar _VI_FAR referenceWaveformHeader[]);
ViStatus _VI_FUNC rsscope_FetchMainWaveformMeasurement (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViInt32 statisticType,
                                                        ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_FetchAmplitudeTimeWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_FetchEyeJitterWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_FetchHistogramWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_FetchSpectrumWaveformMeasurement
             (ViSession instrumentHandle, ViInt32 measurement,
              ViInt32 measurementFunction, ViInt32 statisticType,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsscope_Abort (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureMSOBusState (ViSession instrumentHandle,
                                                ViInt32 bus, ViBoolean state);
ViStatus _VI_FUNC rsscope_ConfigureMSOVisualization (ViSession instrumentHandle,
                                                     ViInt32 bus,
                                                     ViBoolean showDigitalSignals,
                                                     ViBoolean showBus,
                                                     ViInt32 busRepresentation);
ViStatus _VI_FUNC rsscope_ConfigureMSOClockedBusState (ViSession instrumentHandle,
                                                       ViInt32 bus,
                                                       ViBoolean enableClockedBus);
ViStatus _VI_FUNC rsscope_ConfigureMSOClockedBus (ViSession instrumentHandle,
                                                  ViInt32 bus, ViInt32 clockSource);
ViStatus _VI_FUNC rsscope_ConfigureMSOClockedBusSlope (ViSession instrumentHandle,
                                                       ViInt32 bus,
                                                       ViInt32 clockSlope);
ViStatus _VI_FUNC rsscope_ConfigureMSOAssignChannels (ViSession instrumentHandle,
                                                      ViInt32 bus,
                                                      ViInt32 digitalChannel,
                                                      ViBoolean assignState);
ViStatus _VI_FUNC rsscope_ConfigureMSOSignalSelection (ViSession instrumentHandle,
                                                       ViInt32 digitalChannel,
                                                       ViString label,
                                                       ViReal64 deskew);
ViStatus _VI_FUNC rsscope_ConfigureMSODeskew (ViSession instrumentHandle,
                                              ViInt32 bus, ViReal64 deskew);
ViStatus _VI_FUNC rsscope_ConfigureMSOTechnology (ViSession instrumentHandle,
                                                  ViInt32 digitalChannel,
                                                  ViInt32 technology);
ViStatus _VI_FUNC rsscope_ConfigureMSOTresholdSetup (ViSession instrumentHandle,
                                                     ViInt32 digitalChannel,
                                                     ViReal64 treshold,
                                                     ViInt32 hysteresis);
ViStatus _VI_FUNC rsscope_ConfigureMSOTresholdAllChannels
             (ViSession instrumentHandle, ViInt32 bus, ViInt32 technology,
              ViInt32 channelGroup, ViReal64 treshold, ViInt32 hysteresis);
ViStatus _VI_FUNC rsscope_ConfigureMSOChannelCoupling (ViSession instrumentHandle,
                                                       ViInt32 bus,
                                                       ViBoolean coupling);
ViStatus _VI_FUNC rsscope_MSORemoveAllAssignedChannels (ViSession instrumentHandle,
                                                        ViInt32 bus);
ViStatus _VI_FUNC rsscope_ReadSignals (ViSession instrumentHandle,
                                       ViInt32 digitalChannel, ViUInt32 arraySize,
                                       ViInt32 maximumTime,
                                       ViBoolean _VI_FAR signalArray[],
                                       ViInt32* actualPoints);
ViStatus _VI_FUNC rsscope_ConfigureMSOTrigger (ViSession instrumentHandle,
                                               ViInt32 triggerType);
ViStatus _VI_FUNC rsscope_ConfigureMSOEdgeTriggerSource (ViSession instrumentHandle,
                                                         ViInt32 triggerSource,
                                                         ViInt32 triggerSlope,
                                                         ViString expression);
ViStatus _VI_FUNC rsscope_ConfigureMSOWidthTriggerSource (ViSession instrumentHandle,
                                                          ViInt32 triggerSource,
                                                          ViInt32 widthPolarity,
                                                          ViInt32 widthCondition,
                                                          ViReal64 width,
                                                          ViReal64 widthDelta,
                                                          ViString expression);
ViStatus _VI_FUNC rsscope_ConfigureMSOTimeoutTriggerSource
             (ViSession instrumentHandle, ViInt32 triggerSource,
              ViReal64 timeoutValue, ViInt32 timeoutCondition, ViString expression);
ViStatus _VI_FUNC rsscope_ConfigureMSOData2ClockTriggerSource
             (ViSession instrumentHandle, ViInt32 triggerSource,
              ViInt32 clockSource, ViInt32 data2ClockPolarity, ViReal64 holdTime,
              ViReal64 setupTime);
ViStatus _VI_FUNC rsscope_ConfigureMSOStateTriggerSource (ViSession instrumentHandle,
                                                          ViInt32 triggerSource,
                                                          ViInt32 clockSource,
                                                          ViInt32 clockPolarity,
                                                          ViString expression);
ViStatus _VI_FUNC rsscope_ConfigureMSOTriggerChannelState
             (ViSession instrumentHandle, ViInt32 digitalChannel,
              ViInt32 triggerType, ViInt32 statusBit);
ViStatus _VI_FUNC rsscope_ConfigureMSOPatternTriggerSource
             (ViSession instrumentHandle, ViInt32 triggerSource,
              ViInt32 patternMode, ViInt32 timeoutCondition, ViReal64 timeout,
              ViReal64 patternWidth, ViReal64 patternDelta,
              ViInt32 patternCondition, ViString expression);
ViStatus _VI_FUNC rsscope_ConfigureMSOSerialPatternTriggerSource
             (ViSession instrumentHandle, ViInt32 triggerSource,
              ViInt32 patternPolarity, ViInt32 clockSource, ViString pattern,
              ViString expression);
ViStatus _VI_FUNC rsscope_QueryMSOBusData (ViSession instrumentHandle, ViInt32 bus,
                                           ViInt32 arraySize,
                                           ViReal64 _VI_FAR results[],
                                           ViInt32* numberOfResults);
ViStatus _VI_FUNC rsscope_QueryMSOChannelData (ViSession instrumentHandle,
                                               ViInt32 digitalChannel,
                                               ViInt32 arraySize,
                                               ViReal64 _VI_FAR results[],
                                               ViInt32* numberOfResults);
ViStatus _VI_FUNC rsscope_QueryMSOBusDataHeader (ViSession instrumentHandle,
                                                 ViInt32 bus, ViReal64* xStart,
                                                 ViReal64* xStop,
                                                 ViInt32* recordLength,
                                                 ViInt32* numberOfValues);
ViStatus _VI_FUNC rsscope_QueryMSOChannelDataHeader (ViSession instrumentHandle,
                                                     ViInt32 digitalChannel,
                                                     ViReal64* xStart,
                                                     ViReal64* xStop,
                                                     ViInt32* recordLength,
                                                     ViInt32* numberOfValues);
ViStatus _VI_FUNC rsscope_ConfigureIQModeState (ViSession instrumentHandle,
                                                ViBoolean state);
ViStatus _VI_FUNC rsscope_ConfigureIQSamplingInputSettings
             (ViSession instrumentHandle, ViReal64 relativeBandwidth,
              ViReal64 sampleRate, ViInt32 recordLength);
ViStatus _VI_FUNC rsscope_QueryIQSamplingFilterBandwidth (ViSession instrumentHandle,
                                                          ViInt32* filterBandwidth);
ViStatus _VI_FUNC rsscope_ConfigureIQSamplingInputType (ViSession instrumentHandle,
                                                        ViInt32 channel,
                                                        ViInt32 inputType,
                                                        ViInt32 inputMode);
ViStatus _VI_FUNC rsscope_ConfigureIQSamplingRealInput (ViSession instrumentHandle,
                                                        ViInt32 channel,
                                                        ViReal64 carrierFrequency,
                                                        ViInt32 sideband);
ViStatus _VI_FUNC rsscope_ConfigureIQSamplingComplexInput
             (ViSession instrumentHandle, ViInt32 channel, ViReal64 carrierFrequency,
              ViInt32 sideband);
ViStatus _VI_FUNC rsscope_QueryIQData (ViSession instrumentHandle, ViInt32 channel,
                                       ViInt32 arraySize, ViReal64 _VI_FAR i[],
                                       ViReal64 _VI_FAR q[],
                                       ViInt32* numberOfResults);
ViStatus _VI_FUNC rsscope_QueryIQDataMemory (ViSession instrumentHandle,
                                             ViInt32 channel,
                                             ViInt32 skippedSamples,
                                             ViInt32 returnedSamples,
                                             ViInt32 arraySize,
                                             ViReal64 _VI_FAR i[],
                                             ViReal64 _VI_FAR q[],
                                             ViInt32* numberOfResults);
ViStatus _VI_FUNC rsscope_QueryIQDataHeader (ViSession instrumentHandle,
                                             ViInt32 channel, ViReal64* xStart,
                                             ViReal64* xStop, ViInt32* recordLength,
                                             ViInt32* numberOfValues);
ViStatus _VI_FUNC rsscope_reset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_self_test (ViSession instrumentHandle,
                                     ViInt16* selfTestResult,
                                     ViChar _VI_FAR selfTestMessage[]);
ViStatus _VI_FUNC rsscope_revision_query (ViSession instrumentHandle,
                                          ViChar _VI_FAR instrumentDriverRevision[],
                                          ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC rsscope_error_query (ViSession instrumentHandle,
                                       ViInt32* errorCode,
                                       ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC rsscope_error_message (ViSession instrumentHandle,
                                         ViStatus errorCode,
                                         ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC rsscope_SetStatusRegister (ViSession instrumentHandle,
                                             ViInt32 questionableRegister,
                                             ViInt32 enable, ViInt32 PTransition,
                                             ViInt32 NTransition);
ViStatus _VI_FUNC rsscope_GetStatusRegister (ViSession instrumentHandle,
                                             ViInt32 questionableRegister,
                                             ViInt32 registerPart,
                                             ViInt32* registerValue);
ViStatus _VI_FUNC rsscope_ConfigureErrorChecking (ViSession instrumentHandle,
                                                  ViBoolean optionChecking,
                                                  ViBoolean rangeChecking,
                                                  ViBoolean statusChecking);

ViStatus _VI_FUNC rsscope_SetOPCTimeout (ViSession instrumentHandle,
                                         ViUInt32 timeout);

ViStatus _VI_FUNC rsscope_GetOPCTimeout (ViSession instrumentHandle,
                                         ViUInt32 *timeout);

ViStatus _VI_FUNC rsscope_GetError (ViSession instrumentHandle, ViStatus* code,
                                    ViInt32 bufferSize,
                                    ViChar _VI_FAR description[]);
ViStatus _VI_FUNC rsscope_ClearError (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_WriteInstrData (ViSession instrumentHandle,
                                          ViChar _VI_FAR writeBuffer[]);
ViStatus _VI_FUNC rsscope_ReadInstrData (ViSession instrumentHandle,
                                         ViInt32 numberOfBytesToRead,
                                         ViChar _VI_FAR readBuffer[],
                                         ViUInt32* numBytesRead);
ViStatus _VI_FUNC rsscope_QueryViBoolean (ViSession instrumentHandle,
                                          ViString command, ViBoolean* value);
ViStatus _VI_FUNC rsscope_QueryViInt32 (ViSession instrumentHandle,
                                        ViString command, ViInt32* value);
ViStatus _VI_FUNC rsscope_QueryViReal64 (ViSession instrumentHandle,
                                         ViString command, ViReal64* value);
ViStatus _VI_FUNC rsscope_QueryViString (ViSession instrumentHandle,
                                         ViString command, ViInt32 bufferSize,
                                         ViChar _VI_FAR value[]);
ViStatus _VI_FUNC rsscope_FileManagerOperations (ViSession instrumentHandle,
                                                 ViInt32 operation, ViString source,
                                                 ViString destination);
ViStatus _VI_FUNC rsscope_FileCount (ViSession instrumentHandle, ViString directory,
                                     ViInt32* numberOfFilesAndFolders);
ViStatus _VI_FUNC rsscope_FileDirectoryContent (ViSession instrumentHandle,
                                                ViString directory,
                                                ViInt32 bufferSize,
                                                ViChar _VI_FAR output[]);
ViStatus _VI_FUNC rsscope_FileSubdirectoriesCount (ViSession instrumentHandle,
                                                   ViString directory,
                                                   ViInt32* numberOfSubdirectories);
ViStatus _VI_FUNC rsscope_FileSubdirectories (ViSession instrumentHandle,
                                              ViString directory,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR output[]);
ViStatus _VI_FUNC rsscope_FileDrives (ViSession instrumentHandle,
                                      ViInt32 bufferSize, ViChar _VI_FAR output[]);
ViStatus _VI_FUNC rsscope_ReadToFileFromInstrument (ViSession instrumentHandle,
                                                    ViString source,
                                                    ViString destination);
ViStatus _VI_FUNC rsscope_WriteFromFileToInstrument (ViSession instrumentHandle,
                                                     ViString source,
                                                     ViString destination);
ViStatus _VI_FUNC rsscope_DataSetFileOperations (ViSession instrumentHandle,
                                                 ViInt32 operation,
                                                 ViInt32 stateNumber,
                                                 ViString path);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportSource (ViSession instrumentHandle,
                                                         ViInt32 source);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportScopeZoom
             (ViSession instrumentHandle, ViString diagramName, ViString zoomName);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportScopeCursor
             (ViSession instrumentHandle, ViInt32 cursor);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportScopeGate
             (ViSession instrumentHandle, ViInt32 measurement);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportScopeManual
             (ViSession instrumentHandle, ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportScopeComplete
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsscope_ConfigureWaveformExportScopeDataLogging
             (ViSession instrumentHandle, ViBoolean dataLogging);
ViStatus _VI_FUNC rsscope_WaveformExportInterleavedXY (ViSession instrumentHandle,
                                                       ViBoolean interleavedXY);
ViStatus _VI_FUNC rsscope_WaveformExportRawValues (ViSession instrumentHandle,
                                                   ViBoolean rawValues);
ViStatus _VI_FUNC rsscope_WaveformExportFile (ViSession instrumentHandle,
                                              ViString file);
ViStatus _VI_FUNC rsscope_close (ViSession instrumentHandle);


/****************************************************************************
 *------------------------ Error And Completion Codes ----------------------*
 ****************************************************************************/

#define RSSCOPE_WARN_MEASURE_UNCALIBRATED    (RS_CLASS_WARN_BASE + 0x0001L)
#define RSSCOPE_WARN_OVER_RANGE              (RS_CLASS_WARN_BASE + 0x0002L)
#define RSSCOPE_WARN_DATA_NOT_AVAILABLE      (RS_CLASS_WARN_BASE + 0x0003L)

#define RSSCOPE_ERROR_MARKER_NOT_ENABLED     (RS_CLASS_ERROR_BASE + 0x0003L)
#define RSSCOPE_ERROR_NOT_DELTA_MARKER       (RS_CLASS_ERROR_BASE + 0x0002L)
#define RSSCOPE_ERROR_MAX_TIME_EXCEEDED      (RS_CLASS_ERROR_BASE + 0x0001L)

#define RSSCOPE_WARNMSG_MEASURE_UNCALIBRATED "Uncalibrated measurement"
#define RSSCOPE_WARNMSG_OVER_RANGE           "Measurement overrange"
#define RSSCOPE_WARNMSG_DATA_NOT_AVAILABLE   "Measurement data not available"

#define RSSCOPE_ERRMSG_MARKER_NOT_ENABLED    "Marker Not Enabled"
#define RSSCOPE_ERRMSG_NOT_DELTA_MARKER      "Not Delta Marker"
#define RSSCOPE_ERRMSG_MAX_TIME_EXCEEDED     "Max Time Exceeded"

#define RSSCOPE_ERROR_CODES_AND_MSGS \
    {RSSCOPE_WARN_MEASURE_UNCALIBRATED,  RSSCOPE_WARNMSG_MEASURE_UNCALIBRATED},\
    {RSSCOPE_WARN_OVER_RANGE,            RSSCOPE_WARNMSG_OVER_RANGE},\
    {RSSCOPE_WARN_DATA_NOT_AVAILABLE,    RSSCOPE_WARNMSG_DATA_NOT_AVAILABLE},\
    {RSSCOPE_ERROR_MARKER_NOT_ENABLED,   RSSCOPE_ERRMSG_MARKER_NOT_ENABLED},\
    {RSSCOPE_ERROR_NOT_DELTA_MARKER,     RSSCOPE_ERRMSG_NOT_DELTA_MARKER},\
    {RSSCOPE_ERROR_NOT_DELTA_MARKER,     RSSCOPE_ERRMSG_NOT_DELTA_MARKER},\
    {RSSCOPE_ERROR_MAX_TIME_EXCEEDED,    RSSCOPE_ERRMSG_MAX_TIME_EXCEEDED}

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __RSSCOPE_HEADER */



