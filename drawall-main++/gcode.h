/* gcode.h - Déclarations pour l'interprétation du G-code */

#ifndef GCODE_H
#define GCODE_H

#include <stdbool.h>

void gcode_execute_line(char *line);
bool parse_gcode(char *line, float *x, float *y, float *feed_rate);

#endif


/* chat gpt
 * #ifndef GCODEREADER_H
#define GCODEREADER_H

#include <QString>
#include <QFile>
#include <QTextStream>

class GCodeReader
{
public:
    // Constructor
    GCodeReader(const QString &filePath);

    // Method to open the G-code file
    bool openFile();

    // Method to read the file line by line
    void readFile();

    // Method to parse the G-code line (optional)
    void parseGCodeLine(const QString &line);

    // Method to close the file after reading
    void closeFile();

private:
    QString m_filePath; // Path to the G-code file
    QFile m_file;       // QFile object to handle the file
    QTextStream m_in;   // QTextStream object to read the file
};

#endif // GCODEREADER_H
*/
