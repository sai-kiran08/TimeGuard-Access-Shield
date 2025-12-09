# TimeGuard Access Shield
### Password-Controlled Time-Restricted Machine Operation System

TimeGuard Access Shield is a secure embedded access-control system that ensures only authorized users can operate a machine, and only during valid working hours.  
This system enhances safety, prevents unauthorized usage, and enables reliable automation in industrial or controlled environments.

---
## Editing Menu Options

The system provides the following editable parameters:

1. **Real-Time Clock Editing**  
2. **Working Hours Adjustment** (incrementing and decrementing)  
3. **Password Update**  
4. **Exit Menu**

---

## System Architecture Overview

The project consists of multiple C files, each handling a dedicated module:

- **@project_upd1.c**  
  Contains the `main()` function and system initialization logic.

- **@displaysec.c**  
  Handles LCD display routines, RTC display, and menu display when an interrupt occurs.

- **@editsec.c**  
  Contains functions for editing:
  - Time  
  - Date  
  - Day  
  - Working hours  
  - Password updates  

- **@authenti.c**  
  Contains authentication logic, password validation, and time-based access checking.

---
## How the System Works 

1. System boots → RTC displayed.  
2. User presses **'A'** → Password entry mode activates.  
3. System verifies password.  
4. If correct → system checks whether the time is within working hours.  
5. If both conditions are satisfied → machine access granted.  
6. Interrupt switch at any time → open settings menu.  

---

## Hardware / Module Requirements

- Microcontroller (ARM7 LPC21XX)  
- 16x2 LCD Display  
- Keypad Matrix (4*4) 
- RTC Module  
- VIC  (Vector interrupt controller)  
