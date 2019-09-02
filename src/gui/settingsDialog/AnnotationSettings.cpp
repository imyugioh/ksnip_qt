/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "AnnotationSettings.h"

AnnotationSettings::AnnotationSettings(KsnipConfig *config)
{
    Q_ASSERT(config != nullptr);

    mConfig = config;

    initGui();
    loadConfig();
}

AnnotationSettings::~AnnotationSettings()
{
    delete mSmoothPathCheckbox;
    delete mItemShadowCheckbox;
    delete mTextFontLabel;
    delete mNumberFontLabel;
    delete mSmoothFactorLabel;
    delete mWatermarkImageLabel;
    delete mSmoothFactorCombobox;
    delete mTextFontCombobox;
    delete mNumberFontCombobox;
    delete mTextBoldButton;
    delete mTextItalicButton;
    delete mTextUnderlineButton;
    delete mUpdateWatermarkImageButton;
    delete mLayout;
}

void AnnotationSettings::saveSettings()
{
    mConfig->setTextFont(mTextFontCombobox->currentFont());
    mConfig->setTextBold(mTextBoldButton->isChecked());
    mConfig->setTextItalic(mTextItalicButton->isChecked());
    mConfig->setTextUnderline(mTextUnderlineButton->isChecked());
    mConfig->setNumberFont(mNumberFontCombobox->currentFont());
    mConfig->setItemShadowEnabled(mItemShadowCheckbox->isChecked());
    mConfig->setSmoothPathEnabled(mSmoothPathCheckbox->isChecked());
    mConfig->setSmoothFactor(mSmoothFactorCombobox->value());
}

void AnnotationSettings::initGui()
{
    auto const fixedButtonSize = 100;

    mSmoothPathCheckbox = new QCheckBox(this);
    mItemShadowCheckbox = new QCheckBox(this);
    mTextFontLabel = new QLabel(this);
    mNumberFontLabel = new QLabel(this);
    mSmoothFactorLabel = new QLabel(this);
    mWatermarkImageLabel = new QLabel(this);
    mSmoothFactorCombobox = new NumericComboBox(1, 1, 15);
    mTextFontCombobox = new QFontComboBox(this);
    mNumberFontCombobox = new QFontComboBox(this);
    mTextBoldButton = new QToolButton(this);
    mTextItalicButton = new QToolButton(this);
    mTextUnderlineButton = new QToolButton(this);
    mUpdateWatermarkImageButton = new QPushButton(this);
    mLayout = new QGridLayout(this);

    mItemShadowCheckbox->setText(tr("Paint Item Shadows"));
    mItemShadowCheckbox->setToolTip(tr("When enabled, paint items cast shadows."));

    mSmoothPathCheckbox->setText(tr("Smooth Painter Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and\n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, &QCheckBox::clicked, this, &AnnotationSettings::smoothPathCheckboxClicked);

    mSmoothFactorLabel->setText(tr("Smooth Factor") + QStringLiteral(":"));
    mSmoothFactorLabel->setToolTip(tr("Increasing the smooth factor will decrease\n"
                                      "precision for pen and marker but will\n"
                                      "make them more smooth."));
    mSmoothFactorCombobox->setMinimumWidth(fixedButtonSize);
    mSmoothFactorCombobox->setToolTip(mSmoothFactorLabel->toolTip());

    mTextFontLabel->setText(tr("Text Font") + QStringLiteral(":"));
    mTextFontLabel->setToolTip(tr("Sets the font for the Text Paint Item."));
    mTextFontCombobox->setToolTip(mTextFontLabel->toolTip());
    mTextFontCombobox->setEditable(false);

    mTextBoldButton->setIcon(IconLoader::load(QStringLiteral("bold.svg")));
    mTextBoldButton->setToolTip(tr("Bold"));
    mTextBoldButton->setCheckable(true);

    mTextItalicButton->setIcon(IconLoader::load(QStringLiteral("italic.svg")));
    mTextItalicButton->setToolTip(tr("Italic"));
    mTextItalicButton->setCheckable(true);

    mTextUnderlineButton->setIcon(IconLoader::load(QStringLiteral("underline.svg")));
    mTextUnderlineButton->setToolTip(tr("Underline"));
    mTextUnderlineButton->setCheckable(true);

    mNumberFontLabel->setText(tr("Numbering Font") + QStringLiteral(":"));
    mNumberFontLabel->setToolTip(tr("Sets the font for the Numbering Paint Item."));
    mNumberFontCombobox->setToolTip(mNumberFontLabel->toolTip());
    mNumberFontCombobox->setEditable(false);

    mWatermarkImageLabel->setPixmap(mWatermarkImageLoader.load());
    mWatermarkImageLabel->setToolTip(tr("Watermark Image"));
    mWatermarkImageLabel->setAutoFillBackground(true);
    mWatermarkImageLabel->setFixedWidth(100);
    mWatermarkImageLabel->setFixedHeight(100);
    mWatermarkImageLabel->setScaledContents(true);
    mWatermarkImageLabel->setStyleSheet(QStringLiteral("QLabel { background-color : white; }"));
    mUpdateWatermarkImageButton->setText(tr("Update"));
	connect(mUpdateWatermarkImageButton, &QPushButton::clicked, this, &AnnotationSettings::updateWatermarkImageClicked);

    mLayout->setAlignment(Qt::AlignTop);
    mLayout->setColumnStretch(1, 1);
    mLayout->addWidget(mItemShadowCheckbox, 0, 0, 1, 2);
    mLayout->setRowMinimumHeight(1, 15);
    mLayout->addWidget(mSmoothPathCheckbox, 2, 0, 1, 2);
    mLayout->addWidget(mSmoothFactorLabel, 3, 0);
    mLayout->addWidget(mSmoothFactorCombobox, 3, 1, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(4, 15);
    mLayout->addWidget(mTextFontLabel, 5, 0);
    mLayout->addWidget(mTextFontCombobox, 5, 1);
    mLayout->addWidget(mTextBoldButton, 5, 2);
    mLayout->addWidget(mTextItalicButton, 5, 3);
    mLayout->addWidget(mTextUnderlineButton, 5, 4);
    mLayout->addWidget(mNumberFontLabel, 6, 0);
    mLayout->addWidget(mNumberFontCombobox, 6, 1);
    mLayout->addWidget(mWatermarkImageLabel, 7, 0);
    mLayout->addWidget(mUpdateWatermarkImageButton, 7, 1, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(7, 15);

    setTitle(tr("Painter Settings"));
    setLayout(mLayout);
}

void AnnotationSettings::loadConfig()
{
    mTextFontCombobox->setCurrentFont(mConfig->textFont());
    mTextBoldButton->setChecked(mConfig->textBold());
    mTextItalicButton->setChecked(mConfig->textItalic());
    mTextUnderlineButton->setChecked(mConfig->textUnderline());
    mNumberFontCombobox->setCurrentFont(mConfig->numberFont());
    mItemShadowCheckbox->setChecked(mConfig->itemShadowEnabled());
    mSmoothPathCheckbox->setChecked(mConfig->smoothPathEnabled());
    mSmoothFactorCombobox->setValue(mConfig->smoothFactor());
    smoothPathCheckboxClicked(mConfig->smoothPathEnabled());
}

void AnnotationSettings::smoothPathCheckboxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}

void AnnotationSettings::updateWatermarkImageClicked()
{
	UpdateWatermarkOperation operation(this);
	auto successful = operation.execute();

	if(successful) {
		mWatermarkImageLabel->setPixmap(mWatermarkImageLoader.load());
	}
}
