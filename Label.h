//
// Created by Gchiko on 03-Jan-19.
//

#ifndef UNIONFIND_LABEL_H
#define UNIONFIND_LABEL_H

class Label {
    int label_id; // id of the label.
    int score; // score that match the label.
    int max_label; // the label with the highest score in the subtree.
    int max_score; // the highest score in the subtree.

public:

    /**
     * basic c'tor' constructs a label with given score.
     * @param score - the score that match the label.
     */
    Label(int label, int score) : label_id(label), score(score), max_label(-1), max_score(-1) {}


    /**
     * get label_id field.
     * @return label_id.
     */
    int getLabel_id() const {
        return label_id;
    }


    /**
     * get score field.
     * @return score field.
     */
    int getScore() const {
        return score;
    }

    /**
     * set score field with new given score.
     * @param score - the new score.
     */
    void setScore(int score) {
        this->score = score;
    }

    /**
     * get max_label field.
     * @return max_label field.
     */
    int getMax_label() const {
        return max_label;
    }

    /**
     * set max_label field with new given max_label.
     * @param max_label - the new max_label.
     */
    void setMax_label(int max_label) {
        this->max_label = max_label;
    }

    /**
     * get max_score field.
     * @return max_score field.
     */
    int getMax_score() const {
        return max_score;
    }

    /**
     * set max_score field with new given max_score.
     * @param max_score - the new max_score.
     */
    void setMax_score(int max_score) {
        this->max_score = max_score;
    }
};

#endif //UNIONFIND_LABEL_H
