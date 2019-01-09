//
// Created by Gchiko on 03-Jan-19.
//

#ifndef UNIONFIND_LABEL_H
#define UNIONFIND_LABEL_H

#include <ostream>


class Label {
    int label_id=-1; // id of the label.
    int score=-1; // score that match the label.
    int max_label=-1; // the label with the highest score in the subtree.
    int max_score=-1; // the highest score in the subtree.

public:
    friend ostream& operator<<(ostream& os, const Label& label);

    /**
     * basic c'tor' constructs a label with given score.
     * @param score - the score that match the label.
     */
    Label(int label, int score) : label_id(label), score(score), max_label(-1), max_score(-1) {}

    /**
     * copy c'tor constructs a label by
     * @param label - the given label
     */

    Label(const Label& label) : label_id(label.label_id), score(label.score),
                                 max_label(label.max_label),
                                 max_score(label.max_score) {}


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





inline ostream& operator<<(ostream& os, const Label& label) {
    return os << "label id: " << label.label_id << " label score: "  << label.score << " label max_score: " << label.max_score << " label max_label: " <<label.max_label << "\n";
}


#endif //UNIONFIND_LABEL_H
