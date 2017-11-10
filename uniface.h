#ifndef UNIFACE_H
#define UNIFACE_H

#include <QObject>
#include <QGraphicsView>
#include <QPointer>

#include <fileworker.h>
#include <globalvarfromresourcesloader.h>

class UniFace: public QObject {
	Q_OBJECT
	public:
		explicit UniFace(QObject* parent = 0);
		virtual ~UniFace();

		QPointer<QGraphicsView> graphicsView = nullptr;

	public slots:
		void setNewModel(QList<QGraphicsScene*> model, ModelConfigs modelConfigs);
		void resize();

	private:
		QList<QGraphicsScene*> interfacesModel;

	private slots:
		void changeScene(QGraphicsScene* scene);
};

#endif // UNIFACE_H
