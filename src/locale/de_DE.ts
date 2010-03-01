<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="de_DE">
<context>
    <name>AboutDialog</name>
    <message>
        <location filename="../gui/dialogs/aboutdialog.ui" line="14"/>
        <source>About Masonry</source>
        <translation>Über Masonry</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/aboutdialog.ui" line="47"/>
        <source>Masonry</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/aboutdialog.ui" line="54"/>
        <source>%1 (http://%2)</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/aboutdialog.ui" line="61"/>
        <location filename="../gui/dialogs/aboutdialog.cpp" line="33"/>
        <source>Version %1</source>
        <translation></translation>
    </message>
    <message utf8="true">
        <location filename="../gui/dialogs/aboutdialog.ui" line="68"/>
        <source>Copyright (c) 2009 ifak - Institut für Automation und Kommunikation e.V.</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/aboutdialog.ui" line="78"/>
        <source>A graphical tool to visualize and compute Mason-graphs.</source>
        <translation>Ein grafisches Werkzeug zum Visualisieren und Bearbeiten von Mason-Graphen.</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/aboutdialog.cpp" line="32"/>
        <source>&lt;strong&gt;%1 e.V.&lt;/strong&gt; (&lt;a href=&quot;%2&quot;&gt;%2&lt;/a&gt;)</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>ConfigDialog</name>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="14"/>
        <source>Configuration</source>
        <translation>Konfiguration</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="42"/>
        <location filename="../gui/dialogs/configdialog.ui" line="92"/>
        <source>General</source>
        <translation>Allgemein</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="54"/>
        <location filename="../gui/dialogs/configdialog.ui" line="245"/>
        <source>View</source>
        <translation>Ansicht</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="65"/>
        <location filename="../gui/dialogs/configdialog.ui" line="323"/>
        <source>Backend</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="128"/>
        <source>Custom Scripts</source>
        <translation>Eigene Skripte</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="134"/>
        <location filename="../gui/dialogs/configdialog.ui" line="161"/>
        <location filename="../gui/dialogs/configdialog.ui" line="208"/>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Sans Serif&apos;; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Your script must have a function of the same name as the file name and those parameters:&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600; color:#000000;&quot;&gt;    Eq&lt;/span&gt;	- Resulting equation&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600; color:#000000;&quot;&gt;    Num&lt;/span&gt;	- Numerator&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600; color:#000000;&quot;&gt;    Den&lt;/span&gt;	- Denominator&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;A minimal script might look like this:&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-style:italic;&quot;&gt;    function dummy(Eq,Num,Den)&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-style:italic;&quot;&gt;        fprintf(&apos;Dummy Function\n&apos;);&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-style:italic;&quot;&gt;    end&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Sans Serif&apos;; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Ihre Skripte müssen eine Funktion mit dem selben Namen der Datei haben und diese Parameter akzeptieren:&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600; color:#000000;&quot;&gt;    Eq&lt;/span&gt;	- Resultierende Gleichung&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600; color:#000000;&quot;&gt;    Num&lt;/span&gt;	- Zähler&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-weight:600; color:#000000;&quot;&gt;    Den&lt;/span&gt;	- Nenner&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Ein minimales Beispielskript könnte so aussehen:&lt;/p&gt;
&lt;p style=&quot;-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-style:italic;&quot;&gt;    function dummy(Eq,Num,Den)&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-style:italic;&quot;&gt;        fprintf(&apos;Dummy Function\n&apos;);&lt;/span&gt;&lt;/p&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;&lt;span style=&quot; font-style:italic;&quot;&gt;    end&lt;/span&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="151"/>
        <source>Here you can add additional custom scripts that are run after the main computation:</source>
        <translation>Hier können sie zusätzliche eigene Skripten hinzufügen, die nach der eigentlichen Berechnung ausgeführt werden:</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="178"/>
        <source>Add Script...</source>
        <translation>Füge Skript hinzu...</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="188"/>
        <source>Remove Selected Script</source>
        <translation>Entferne ausgewähltes Skript</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="268"/>
        <source>GroupBox</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="274"/>
        <location filename="../gui/dialogs/configdialog.ui" line="290"/>
        <source>TODO</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="284"/>
        <source>Advanced</source>
        <translation>Fortgeschritten</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="344"/>
        <source>External Octave Interpreter</source>
        <translation>Externer Octave-Interpreter</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="349"/>
        <source>External Matlab Interpreter</source>
        <translation>Externer Matlab-Interpreter</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="373"/>
        <source>Octave Options</source>
        <translation>Octave-Optionen</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="379"/>
        <location filename="../gui/dialogs/configdialog.ui" line="428"/>
        <source>Executable:</source>
        <translation>Programm:</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="389"/>
        <location filename="../gui/dialogs/configdialog.ui" line="438"/>
        <source>Parameters:</source>
        <translation>Parameter:</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="405"/>
        <location filename="../gui/dialogs/configdialog.ui" line="454"/>
        <source>...</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.ui" line="422"/>
        <source>Matlab Options</source>
        <translation>Matlab-Optionen</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.cpp" line="58"/>
        <source>Please Select Octave Executable</source>
        <translation>Bitte wählen Sie das Octave-Programm aus</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.cpp" line="60"/>
        <source>Octave Executable (%1)</source>
        <translation>Octave-Programm (%1)</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.cpp" line="69"/>
        <source>Please Select Matlab Executable</source>
        <translation>Bitte wählen Sie das Matlab-Programm aus</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.cpp" line="71"/>
        <source>Matlab Executable (%1)</source>
        <translation>Matlab-Programm (%1)</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.cpp" line="80"/>
        <source>Add Matlab Script File</source>
        <translation>Füge Matlab-Skript hinzu</translation>
    </message>
    <message>
        <location filename="../gui/dialogs/configdialog.cpp" line="82"/>
        <source>Matlab Script Files</source>
        <translation>Matlab-Skript Dateien</translation>
    </message>
</context>
<context>
    <name>EditDockWidget</name>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="14"/>
        <location filename="../gui/widgets/editdockwidget.cpp" line="63"/>
        <source>Edit</source>
        <translation>Bearbeiten</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="31"/>
        <source>Please select an Item.</source>
        <translation>Bitte wählen Sie ein Objekt aus.</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="48"/>
        <location filename="../gui/widgets/editdockwidget.ui" line="104"/>
        <source>Name:</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="64"/>
        <source>Delete Edge</source>
        <translation>Lösche Kante</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="87"/>
        <location filename="../gui/widgets/editdockwidget.ui" line="143"/>
        <source>Formula:</source>
        <translation>Formel:</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="117"/>
        <source>Delete Node</source>
        <translation>Lösche Knoten</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="157"/>
        <source>Input Node</source>
        <translation>Eingabeknoten</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="162"/>
        <source>Output Node</source>
        <translation>Ausgabeknoten</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="167"/>
        <source>Standard Node</source>
        <translation>Standardknoten</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.ui" line="175"/>
        <source>Type:</source>
        <translation>Typ:</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.cpp" line="53"/>
        <source>Edit Edge</source>
        <translation>Bearbeite Kante</translation>
    </message>
    <message>
        <location filename="../gui/widgets/editdockwidget.cpp" line="59"/>
        <source>Edit Node</source>
        <translation>Bearbeite Knoten</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../gui/mainwindow.ui" line="14"/>
        <source>Masonry - Mason-Graph Lab</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="29"/>
        <source>File</source>
        <translation>Datei</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="40"/>
        <source>Edit</source>
        <translation>Bearbeiten</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="51"/>
        <source>View</source>
        <translation>Ansicht</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="62"/>
        <source>Graph</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="82"/>
        <source>&amp;File</source>
        <translation>&amp;Datei</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="94"/>
        <location filename="../gui/mainwindow.ui" line="176"/>
        <source>&amp;Help</source>
        <translation>&amp;Hilfe</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="103"/>
        <source>&amp;View</source>
        <translation>&amp;Ansicht</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="147"/>
        <source>&amp;Settings</source>
        <translation>&amp;Einstellungen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="151"/>
        <source>Toolbars</source>
        <translation>Werkzeugleisten</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="156"/>
        <source>Dockers</source>
        <translation>Docker</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="111"/>
        <source>&amp;Edit</source>
        <translation>&amp;Bearbeiten</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="122"/>
        <source>&amp;Graph</source>
        <translation>&amp;Graph</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="126"/>
        <source>&amp;Columns</source>
        <translation>&amp;Spalten</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="133"/>
        <source>&amp;Rows</source>
        <translation>&amp;Zeilen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="179"/>
        <source>Help</source>
        <translation>Hilfe</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="182"/>
        <source>Ctrl+?</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="187"/>
        <source>&amp;About</source>
        <translation>&amp;Über</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="190"/>
        <source>About</source>
        <translation>Über</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="198"/>
        <source>&amp;Quit</source>
        <translation>&amp;Beenden</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="201"/>
        <source>Ctrl+Q</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="209"/>
        <source>&amp;New</source>
        <translation>&amp;Neu</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="212"/>
        <source>Ctrl+N</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="217"/>
        <source>&amp;Load...</source>
        <translation>&amp;Laden...</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="220"/>
        <source>Load</source>
        <translation>Laden</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="223"/>
        <source>Ctrl+O</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="228"/>
        <source>Save &amp;As...</source>
        <translation>Speichern &amp;als ...</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="231"/>
        <source>Save As...</source>
        <translation>Speichern als...</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="234"/>
        <source>Ctrl+S</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="242"/>
        <source>&amp;Cut</source>
        <translation>&amp;Ausschneiden</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="245"/>
        <source>Ctrl+X</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="253"/>
        <source>Co&amp;py</source>
        <translation>&amp;Kopieren</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="256"/>
        <source>Ctrl+C</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="264"/>
        <source>&amp;Paste</source>
        <translation>&amp;Einfügen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="267"/>
        <source>Ctrl+V</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="275"/>
        <source>&amp;Undo</source>
        <translation>&amp;Rückgängig</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="278"/>
        <source>Undo Last Action</source>
        <translation>Letzte Aktion zurücksetzen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="281"/>
        <source>Ctrl+Z</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="289"/>
        <source>&amp;Redo</source>
        <translation>&amp;Wiederherstellen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="292"/>
        <source>Redo Last Action</source>
        <translation>Letzte Aktion wiederherstellen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="295"/>
        <source>Ctrl+R</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="300"/>
        <source>Add Row</source>
        <translation>Füge Zeile hinzu</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="308"/>
        <source>Remove Row</source>
        <translation>Zeile löschen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="313"/>
        <source>&amp;Configure Masonry...</source>
        <translation>&amp;Konfiguriere Masonry...</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="316"/>
        <source>Configure Masonry</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="324"/>
        <source>&amp;Save</source>
        <translation>&amp;Speichern</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="329"/>
        <source>About &amp;Qt</source>
        <translation>Über &amp;Qt</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="337"/>
        <source>&amp;Compute Signal</source>
        <translation>&amp;Berechne Signal</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="342"/>
        <source>Zoom &amp;In</source>
        <translation>Ver&amp;größern</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="345"/>
        <source>Ctrl++</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="350"/>
        <source>Zoom &amp;Out</source>
        <translation>Ver&amp;kleinern</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="353"/>
        <source>Ctrl+-</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="361"/>
        <source>Zoom to Fit</source>
        <translation>Ansicht einpassen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="366"/>
        <source>Add Column</source>
        <translation>Füge Spalte hinzu</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="374"/>
        <source>Remove Column</source>
        <translation>Spalte löschen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="382"/>
        <source>&amp;Delete Selected Item</source>
        <translation>&amp;Lösche ausgewähltes Objekt</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.ui" line="390"/>
        <source>&amp;Stop Computation</source>
        <translation>&amp;Breche Berechnung ab</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="69"/>
        <source>Ready</source>
        <translation>Fertig</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="99"/>
        <source>Masonry</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="100"/>
        <source>This graph has been modfied.</source>
        <translation>Dieser Graph wurde verändert.</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="101"/>
        <source>Do you want to save your changes?</source>
        <translation>Wollen Sie ihre Änderungen speichern?</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="123"/>
        <source>Open Masonry Graph File</source>
        <translation>Öffne Masonry Graphen-Datei</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="125"/>
        <location filename="../gui/mainwindow.cpp" line="153"/>
        <source>Masonry Graph Files</source>
        <translation>Masonry Graphen-Dateien</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="169"/>
        <source>Input:</source>
        <translation>Eingabe:</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="217"/>
        <source>Command Line:</source>
        <translation>Kommandozeile:</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="218"/>
        <source>Results:</source>
        <translation>Resultat:</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="221"/>
        <source>Compute signal response from input node &apos;%1&apos; to output node &apos;%2&apos;...</source>
        <translation>Berechne Signal-Antwort vom Eingabeknoten &apos;%1&apos; zum Ausgabeknoten &apos;%2&apos;...</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="132"/>
        <source>File &apos;%1&apos; loaded</source>
        <translation>Datei &apos;%1&apos; geladen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="143"/>
        <location filename="../gui/mainwindow.cpp" line="157"/>
        <source>File &apos;%1&apos; saved</source>
        <translation>Datei &apos;%1&apos; gespeichert</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="150"/>
        <source>Save Masonry Graph File</source>
        <translation>Speichere Masonry Graph-Datei</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="223"/>
        <source>Unable to create temporary file!</source>
        <translation>Konnte keine temporäre Datei anlegen!</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="233"/>
        <source>Settings saved</source>
        <translation>Einstellungen gespeichert</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="281"/>
        <source>Computation finished</source>
        <translation>Berechnung abgeschlossen</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="289"/>
        <location filename="../gui/mainwindow.cpp" line="290"/>
        <source>Backend failed to start!</source>
        <translation>Backend konnte nicht gestartet werden!</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="293"/>
        <location filename="../gui/mainwindow.cpp" line="294"/>
        <source>Backend crashed or was stopped!</source>
        <translation>Backend ist abgestürzt oder wurde beendet!</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="297"/>
        <location filename="../gui/mainwindow.cpp" line="298"/>
        <source>Backend timed out!</source>
        <translation>Backend hatte eine Zeitüberschreitung!</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="301"/>
        <location filename="../gui/mainwindow.cpp" line="302"/>
        <source>Backend error occurred!</source>
        <translation>Backend-Fehler aufgetreten!</translation>
    </message>
    <message>
        <location filename="../gui/mainwindow.cpp" line="311"/>
        <source>Zoomed to fit graph in view</source>
        <translation>Ansicht wurde eingepasst</translation>
    </message>
</context>
<context>
    <name>NodeDetailDockWidget</name>
    <message>
        <location filename="../gui/widgets/nodedetaildockwidget.ui" line="14"/>
        <source>Node Detail</source>
        <translation>Knotendetails</translation>
    </message>
    <message>
        <location filename="../gui/widgets/nodedetaildockwidget.ui" line="31"/>
        <source>Please select an node.</source>
        <translation>Bitte wählen Sie einen Knoten aus.</translation>
    </message>
    <message>
        <location filename="../gui/widgets/nodedetaildockwidget.ui" line="48"/>
        <source>Name:</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>OutputDockWidget</name>
    <message>
        <location filename="../gui/widgets/outputdockwidget.ui" line="23"/>
        <source>Backend Output</source>
        <translation>Backend-Ausgabe</translation>
    </message>
</context>
</TS>
