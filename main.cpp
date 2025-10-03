#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WRun.h>

#include <string>
#include <memory>

using namespace Wt;

static std::string escapeHtml(const std::string& s) {
    std::string r;
    r.reserve(s.size());
    for (char ch : s) {
        switch (ch) {
            case '&': r += "&amp;"; break;
            case '<': r += "&lt;"; break;
            case '>': r += "&gt;"; break;
            case '"': r += "&quot;"; break;
            case '\'': r += "&#39;"; break;
            default: r += ch; break;
        }
    }
    return r;
}

class FormWidget : public WContainerWidget {
public:
    FormWidget() {
        setStyleClass("form-container");

        addWidget(std::make_unique<WText>("<header><h1>FOX</h1></header>"));
        addWidget(std::make_unique<WText>("<h2>📋 أدخل بياناتك</h2>"));

        auto* nameEdit = addWidget(std::make_unique<WLineEdit>());
        nameEdit->setPlaceholderText("الاسم الكامل");

        auto* phoneEdit = addWidget(std::make_unique<WLineEdit>());
        phoneEdit->setPlaceholderText("رقم الهاتف");

        auto* nextButton = addWidget(std::make_unique<WPushButton>("التالي"));
        nextButton->setStyleClass("next-button");

        auto* resultText = addWidget(std::make_unique<WText>());

        nextButton->clicked().connect([=] {
            std::string name = escapeHtml(nameEdit->text().toUTF8());
            resultText->setText("<div class='result'><h3>الباش مهندس " + name + "</h3></div>");
        });

        addWidget(std::make_unique<WText>("<footer><p>© FOX</p></footer>"));
    }
};

class IT14App : public WApplication {
public:
    IT14App(const WEnvironment& env) : WApplication(env) {
        setTitle("FOX | دفعة IT 14");
        useStyleSheet("style.css");
        root()->addWidget(std::make_unique<FormWidget>());
    }
};

std::unique_ptr<WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<IT14App>(env);
}

int main(int argc, char** argv) {
    return WRun(argc, argv, &createApplication);
}