\# TravelAgencyGUI ✈️🧳

A comprehensive desktop desktop GUI application designed for orchestrating and managing international tourism bookings, built using \*\*C++/CLI Windows Forms\*\* architecture.



\## 🛠️ System Architecture \& Features

The application implements a strict sequential \*\*Wizard System\*\* distributed across 4 interconnected dynamic views:

1\. \*\*Flight Selection:\*\* Dynamically fetches flight IDs, times, and prices based on chosen destinations (Turkey, KSA, UAE) with automated seating class price factor mapping (Economy / Business).

2\. \*\*Hotel Accommodations:\*\* Implements real-time destination-based content filtering to dynamically query corresponding hotels and computes dynamic stay costs based on input check-in nights.

3\. \*\*Local Activities:\*\* Books location-based entertainment events utilizing custom time-slot allocation logic.

4\. \*\*Final Checkout:\*\* Consolidates state data globally across all forms to present a unified immutable pricing overview before firing explicit completion flags.



\## 💻 Technical Highlights

\* \*\*Global State Management:\*\* Orchestrated state propagation across independent forms without data redunancy via a dedicated unified `SystemController` controller deploying static memory allocations.

\* \*\*Interoperability (Data Marshalling):\*\* Managed internal data structures using standard Native C++ constructs (`std::string`, `std::vector`) and implemented safe cross-boundary data transfers to CLI components using `<msclr/marshal\_cppstd.h>`.

