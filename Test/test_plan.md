
# Smart Classroom Comfort Monitor — Test Cases

**Course:** CSE1106  
**Project:** Smart Classroom Comfort Monitor  
**Repository:** [CSE1106Final](https://github.com/Noah-R-Rodriguez/CSE1106Final)

---

## 1. Introduction

This document outlines the test cases for the Smart Classroom Comfort Monitor application.

The purpose of testing is to verify that the application correctly processes classroom temperature readings, identifies temperatures outside the acceptable range, calculates averages, exports temperature records, and activates an LED warning indicator.

### System Requirements

The application must:

- Accept classroom temperature readings in Fahrenheit.
- Identify temperatures within the acceptable range of 68°F–76°F.
- Display either `NORMAL` or `WARNING`.
- Calculate the average of recorded temperatures.
- Export temperature readings and their corresponding statuses to a `.txt` file.
- Activate an LED when a temperature is outside the acceptable range.
- Allow the acceptable temperature range to be modified.

## 2. Test Environment

| Component | Description |
|---|---|
| Programming language | C |
| Platform | Raspberry Pi |
| Compiler | GCC |
| Operating system | Raspberry Pi OS / Linux |
| Temperature unit | Fahrenheit |
| Default minimum | 68°F |
| Default maximum | 76°F |
| Output format | TXT |

### Testing Considerations

- Software tests should be executable without physical LED hardware where possible.
- LED tests should use a mock or simulated GPIO interface when running on a development machine.
- File-export tests should use a temporary output file.
- Tests should begin with a clean set of temperature records unless otherwise specified.

## 3. Temperature Validation Tests

These tests verify that temperature readings are correctly classified as NORMAL or WARNING.

| Test ID | Test Description | Input | Expected Result |
|---|---|---|---|
| TC-001 | Temperature at minimum acceptable boundary | 68°F | NORMAL |
| TC-002 | Temperature at maximum acceptable boundary | 76°F | NORMAL |
| TC-003 | Temperature below acceptable range | 67°F | WARNING |
| TC-004 | Temperature above acceptable range | 77°F | WARNING |
| TC-005 | Temperature in middle of acceptable range | 72°F | NORMAL |
| TC-006 | Temperature significantly below range | 32°F | WARNING |
| TC-007 | Temperature significantly above range | 100°F | WARNING |
| TC-008 | Temperature just below minimum | 67.9°F | WARNING |
| TC-009 | Temperature just above maximum | 76.1°F | WARNING |

### Acceptance Criteria

- Temperatures greater than or equal to 68°F and less than or equal to 76°F must return NORMAL.
- Temperatures below 68°F must return WARNING.
- Temperatures above 76°F must return WARNING.
- Boundary values must be handled correctly.

## 4. Average Temperature Calculation Tests

These tests verify that the application correctly calculates the average of recorded temperatures.

| Test ID | Test Description | Input | Expected Result |
|---|---|---|---|
| TC-010 | Average of three readings | 70, 72, 74 | 72°F |
| TC-011 | Average of one reading | 75 | 75°F |
| TC-012 | Average of identical readings | 72, 72, 72 | 72°F |
| TC-013 | Average of mixed readings | 60, 70, 80 | 70°F |
| TC-014 | Average including decimal values | 70.5, 71.5, 72.5 | 71.5°F |
| TC-015 | Average of multiple readings | 68, 70, 72, 74, 76 | 72°F |
| TC-016 | Average with no recorded readings | Empty dataset | Handle gracefully; do not divide by zero |

### Acceptance Criteria

- The application must calculate the arithmetic mean correctly.
- Decimal values must be handled without unintended truncation.
- An empty dataset must not cause a division-by-zero error.
- The displayed average must accurately represent the recorded temperatures.

## 5. Temperature Record Management Tests

These tests verify that temperature readings are properly stored and processed.

| Test ID | Test Description | Input | Expected Result |
|---|---|---|---|
| TC-017 | Record a single temperature | 72°F | Reading successfully recorded |
| TC-018 | Record multiple temperatures | 70°F, 72°F, 74°F | All readings recorded |
| TC-019 | Record a normal temperature | 72°F | NORMAL status stored |
| TC-020 | Record a warning temperature | 80°F | WARNING status stored |
| TC-021 | Record consecutive readings | 72°F, 80°F, 65°F | Each reading retains its correct status |

### Acceptance Criteria

- Every accepted reading must be recorded.
- Each reading must have the correct associated status.
- Recording a new reading must not overwrite previous readings unless explicitly intended.

## 6. File Export Tests

These tests verify that temperature readings and their statuses can be exported to a text file.

| Test ID | Test Description | Input | Expected Result |
|---|---|---|---|
| TC-022 | Export one temperature reading | 72°F | TXT file created with reading |
| TC-023 | Export multiple readings | 70°F, 72°F, 80°F | All readings exported |
| TC-024 | Export temperature statuses | Normal and warning readings | Correct statuses included |
| TC-025 | Export empty dataset | No readings | Graceful handling of empty records |
| TC-026 | Export to specified filename | readings.txt | File created at specified location |
| TC-027 | Export when output directory is unavailable | Invalid destination | Error handled gracefully |
| TC-028 | Verify exported file contents | Multiple readings | Contents match recorded data |

### Acceptance Criteria

- The application must create a `.txt` file when export succeeds.
- All recorded temperatures must be included.
- Each temperature must have its corresponding NORMAL or WARNING status.
- Export failures must not crash the application.
- Exported data must accurately reflect the recorded readings.

## 7. LED Warning Indicator Tests

These tests verify that the Raspberry Pi LED correctly indicates whether a temperature is outside the acceptable range.

| Test ID | Test Description | Input | Expected Result |
|---|---|---|---|
| TC-029 | LED activation below minimum | 67°F | LED ON |
| TC-030 | LED activation above maximum | 77°F | LED ON |
| TC-031 | LED deactivation within range | 72°F | LED OFF |
| TC-032 | LED at minimum boundary | 68°F | LED OFF |
| TC-033 | LED at maximum boundary | 76°F | LED OFF |
| TC-034 | LED state changes from normal to warning | 72°F → 80°F | LED changes OFF → ON |
| TC-035 | LED state changes from warning to normal | 80°F → 72°F | LED changes ON → OFF |

### Acceptance Criteria

- The LED must turn ON whenever the temperature is outside the acceptable range.
- The LED must turn OFF whenever the temperature is within the acceptable range.
- The LED state must update when a new temperature reading is processed.
- Hardware-dependent tests should be verified on a Raspberry Pi or through a GPIO mock.

## 8. Configurable Temperature Range Tests

These tests verify that the acceptable temperature range can be modified to meet different client requirements.

| Test ID | Test Description | Configuration | Input | Expected Result |
|---|---|---|---|---|
| TC-036 | Default temperature range | 68–76°F | 72°F | NORMAL |
| TC-037 | Change minimum temperature | 70–76°F | 69°F | WARNING |
| TC-038 | Change maximum temperature | 68–80°F | 78°F | NORMAL |
| TC-039 | Change both boundaries | 60–90°F | 85°F | NORMAL |
| TC-040 | Test new minimum boundary | 70–80°F | 70°F | NORMAL |
| TC-041 | Test new maximum boundary | 70–80°F | 80°F | NORMAL |

### Acceptance Criteria

- The application must use the configured minimum and maximum temperatures.
- Changing the acceptable range must affect temperature classification.
- Boundary values must remain inclusive.
- The default range must remain 68°F–76°F unless modified.

## 9. Error Handling Tests

These tests verify that the application handles unexpected conditions appropriately.

| Test ID | Test Description | Input / Condition | Expected Result |
|---|---|---|---|
| TC-042 | Empty temperature input | No input | Graceful error handling |
| TC-043 | Invalid text input | abc | Input rejected or handled safely |
| TC-044 | Invalid file destination | Unavailable path | Export error reported |
| TC-045 | Empty average dataset | Zero readings | No division by zero |
| TC-046 | Invalid temperature range | Minimum greater than maximum | Configuration rejected or handled safely |
| TC-047 | Missing output file permissions | Read-only destination | Export failure handled gracefully |

## 10. Test Execution Summary

The following table can be completed after running the tests.

| Test Category | Test IDs | Total Tests | Passed | Failed |
|---|---|---:|---:|---:|
| Temperature Validation | TC-001–TC-009 | 9 | TBD | TBD |
| Average Calculation | TC-010–TC-016 | 7 | TBD | TBD |
| Record Management | TC-017–TC-021 | 5 | TBD | TBD |
| File Export | TC-022–TC-028 | 7 | TBD | TBD |
| LED Indicator | TC-029–TC-035 | 7 | TBD | TBD |
| Configurable Range | TC-036–TC-041 | 6 | TBD | TBD |
| Error Handling | TC-042–TC-047 | 6 | TBD | TBD |
| **Total** | **TC-001–TC-047** | **47** | **TBD** | **TBD** |

## 11. Overall Acceptance Criteria

The Smart Classroom Comfort Monitor will be considered functionally tested when:

1. All temperature readings are classified correctly.
2. The average temperature is calculated accurately.
3. Temperature records are stored and maintained correctly.
4. Temperature readings and statuses are successfully exported.
5. The LED warning indicator responds correctly to temperature changes.
6. The acceptable temperature range can be modified.
7. Invalid inputs and file errors are handled without unexpected application termination.

## 12. Conclusion

These test cases provide a structured approach to validating the Smart Classroom Comfort Monitor.

They cover the application's primary functionality, boundary conditions, file operations, hardware interaction, configurable requirements, and error handling.

The test execution results should be documented after running the corresponding tests on the application.
