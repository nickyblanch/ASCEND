
namespace MICS
{
#define MICS_6814_NO2 A3
#define MICS_6814_CO A1
#define MICS_6814_NH3 A2

    struct measurement
    {
        int NO2;
        int CO;
        int NH3;
    };

    measurement read(File &log_file)
    {
        measurement r{
            analogRead(MICS_6814_NO2),
            analogRead(MICS_6814_CO),
            analogRead(MICS_6814_NH3)};

        log(r.NO2);
        log(",");
        log(r.CO);
        log(",");
        log(r.NH3);
        log(",");

        return r;
    }

}