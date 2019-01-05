class Zone {
public:
  Zone();
  ~Zone();
  bool getMineStatus();
  void setMineStatus(bool);
  bool getRevealedStatus();
  void setRevealedStatus(bool);
  bool getFlaggedStatus();
  void setFlaggedStatus(bool);
  int getValue();
  void setValue(int);
  int getX();
  void setX(int);
  int getY();
  void setY(int);
private:
  bool isMine; // Keeps track of if the zone is a mine
  bool isRevealed; // Keeps track of if the zone has been revealed
  bool isFlagged; // Keeps track of mines user has flagged
  int value; // 0 to 8, depending on numer of surrounding mines
  int x; // x position
  int y; // y position
};
