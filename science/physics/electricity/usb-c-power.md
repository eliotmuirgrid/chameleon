# USB-C charger compatibility

## Concept

USB-C charging is a negotiation system, not just a plug.

A device asks for specific power profiles (voltage/current pairs).
The charger must offer a matching profile.
If they do not overlap, charging is slower or may fail.

## What to optimize for

For broad compatibility, prefer a charger with many standard USB-C PD steps, not just a high wattage label.

Common useful profile range:

- 5V
- 9V
- 12V
- 15V
- 20V

Different devices tend to prefer different steps:

- phones often use 9V,
- tablets often use 12V,
- laptops often use 15V to 20V.

## Wattage vs compatibility

Wattage is a ceiling, not the whole story.

A 65W charger with limited profiles can be less compatible than a 45W charger with a full profile range.

In practice, a reputable 45W to 100W USB-C PD charger often gives strong coverage for mixed devices.

## Cable note

Cables are secondary.

Most USB-C to USB-C cables support up to 60W, which is enough for many devices.
For higher power (for example 100W laptop charging), use a cable rated for that level.

When charging fails, the charger profile set is usually the first thing to check.

## Mental model

You are not buying "a powerful charger."
You are buying a charger that can speak many electrical dialects.

More dialects (profiles) means more devices that charge reliably.

When charging still fails, walk the [power pipeline (computer won't turn on)](../system/troubleshooting/pipeline/power.md). The people-side analog is [adaptive communication](../communication/adaptive_communication.md)—same idea: **keep the goal**, **match the other party’s profile**. A software-side cousin is path **letter case**: different machines assume different rules for whether `File.txt` and `file.txt` are the “same” name; see [Letter case (for paths and names)](../computer/letter_case.md) and [Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md). Home safety angle: [power delivery safety at home](power/delivery/safety.md). Device quirks: [Sonos Move charging](usb-c-power/sonos/move/charging.md).
