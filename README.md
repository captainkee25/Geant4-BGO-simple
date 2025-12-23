Quick Geant4 simulation that was used during the testing stages of BGO QDC/TDC calibration for the ECAL upgrade of Positronium 1s-2s measurements 2025. The geometry mimics the 3-BGO setup used, where the central crystal was used as the trigger. 

- Particle Source: Na-22 radioactive atom produced at rest, and forced to decay, encapsulated in a small plastic casing
- Detector constructor: three hexagonal prism-shaped BGO crystals, surrounding the source in a triangular format (see screenshots below). These were implemented as SensitiveDetectors that saved energy deposited and the time of entry per event
- Physics List: G4EmStandardPhysics_option4, G4RadioactiveDecayPhysics, G4DecayPhysics)

*Readout.root saves:*
1. A master n-tuple of: event number, BGO copy number, "true" energy deposit (including zeros), timing information (from start of event), and a boolean of whether the track was stopped in the BGO or not. The energies are then smeared with a Gaussian distribution of an energy-dependent resolution, and this "smeared energy" is saved in the last column
2. Histograms of energy deposits in BGO unsmeared (excluding zeros)
3. Histograms of energy deposits in BGO smeared (excluding zeros)
4. At the end of each event, we check to see if middle BGO was triggered, i.e. non-zero energy deposit. If yes, check if there was an energy deposit within 1.5 microseconds (mimics QDC gate) in either of the other two BGOs. Histograms of these coincidences are also saved
5. Histograms of coincidences ONLY if the middle BGO had an energy deposit > 1275keV, to check for the 511 keV peaks in the other two BGOs

<img width="1095" height="588" alt="Screenshot 2025-12-10 085809" src="https://github.com/user-attachments/assets/a537f752-564b-4633-bcd4-6f927027b8ee" />
<img width="1290" height="741" alt="Screenshot 2025-12-10 085837" src="https://github.com/user-attachments/assets/d80778f9-e5e0-4005-80de-107551964d52" />
<img width="1117" height="776" alt="Screenshot 2025-12-10 085907" src="https://github.com/user-attachments/assets/19b0a763-3680-4439-ac35-04cc641485b5" />
<img width="871" height="501" alt="Screenshot 2025-12-10 085921" src="https://github.com/user-attachments/assets/d4a7d181-b354-4ae1-87c3-bfd6b05b754f" />
