#ifndef YEAR__H__
#define YEAR__H__

# include <string>

# include <sstream>

# include <iomanip>

struct Year
{
    std::string name;

    double rating;

    int votes;

    double sum;

    Year()
    {
        this->votes = 0;

        this->sum = 0;
    }

    Year(std::string name)
    {
        this->name = name;

        this-> votes = 0;

        this->sum = 0;
    }

    void add_rating(double new_rating)
    {
        this->votes += 1;

        this->sum += new_rating;

        this->rating = this->sum / (double)this->votes;
    }

    void update_rating(double new_rating, double old_rating)
    {
		if (old_rating == -1){
		   	this->votes += 1;

		    this->sum += new_rating;

		    this->rating = this->sum / (double)this->votes;
		}else if (new_rating == -1){
			this->votes -= 1;

		    this->sum -= old_rating;

		    this->rating = this->sum / (double)this->votes;
		} else{
			 this->sum -= old_rating;

		    this->sum += new_rating;

		    this->rating = this->sum / (double)this->votes;
		}
    }

    void remove_rating(double new_rating, double old_rating)
    {	
		if (new_rating == -1){
		    this->votes -= 1;

		    this->sum -= old_rating;

		    this->rating = this->sum / (double)this->votes;
		}else{
			 this->sum -= old_rating;

		    this->sum += new_rating;

		    this->rating = this->sum / (double)this->votes;
		}
    }

    double get_rating()
    {
        if (this->votes != 0)
        {
			rating = round(rating * 100) / 100;

		    std::stringstream tmp;

		    tmp << std::fixed << std::setprecision (2) << rating;

		    std::string aux = tmp.str();
            return this->rating;
        }
        return -2;
    }
};

#endif  // YEAR__H__


